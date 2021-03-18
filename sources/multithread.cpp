// Copyright 2021 by FORTYSS
#include <multithread.hpp>
void Multith::log(){
    logging::add_common_attributes();
  logging::add_console_log(std::clog, boost::log::keywords::format =
                                          "[%Severity%] %TimeStamp%: %Message%"
                           );

  logging::add_file_log
      (
          boost::log::keywords::file_name = "sample_%N.log",
          boost::log::keywords::rotation_size = 10 * 1024 * 1024,
          boost::log::keywords::time_based_rotation =
              boost::log::sinks::file::rotation_at_time_point(0,
                                                              0,
                                                              0),
          boost::log::keywords::format =
              "[%Severity%][%TimeStamp%]: %Message%"
      );
}
void Multith::start() {
  log();
  for(unsigned int i = 0; i < number_threads; ++i){
    threads.emplace_back(std::thread([&](){
      hashing();
    }));
  }
}

void Multith::hashing() {
  std::chrono::system_clock::time_point start =
      std::chrono::high_resolution_clock::now();
  bool key = true;
  while(key){
    mutex.lock();
    src_str = std::to_string(std::rand());
    hash_hex_str = picosha2::hash256_hex_string(src_str);
    std::chrono::system_clock::time_point end =
        std::chrono::high_resolution_clock::now();
    duration += static_cast<int>(std::chrono::nanoseconds(end - start).count());
    start = end;
    sort(hash_hex_str);
    mutex.unlock();
    std::this_thread::sleep_for(std::chrono::microseconds(2));
  }
}

void Multith::sort(std::string &hash) {
  if(hash_hex_str.substr(60, 4) == end_of_str) {
    BOOST_LOG_SEV(slg, logging::trivial::info) << std::endl
                             << "sourse: " << std::hex << std::stol(src_str)
                             << std::dec
                             << " hash: " << hash
                             << " duration: " << duration
                             << " thread: " << std::this_thread::get_id()
                             << std::endl;
    json j = {
        {"sourse", src_str},
        {"hash_hex", hash_hex_str},
        {"duration", duration}
    };
    true_hashs.push_back(j);
  } else {
    BOOST_LOG_SEV(slg, logging::trivial::trace) << std::endl
                              << "sourse: " << std::hex << std::stol(src_str)
                              << std::dec
                              << " hash: " << hash_hex_str
                              << " thread: " << std::this_thread::get_id()
                              << std::endl;
  }
}
std::vector<json> Multith::true_hashs;