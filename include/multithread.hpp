// Copyright 2021 by FORTYSS

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_
#include "../third-party/PicoSHA2/picosha2.h"
#include <thread>
#include <csignal>
#include <nlohmann/json.hpp>
#include <mutex>

#include <boost/log/trivial.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
using json = nlohmann::json;

namespace logging = boost::log;

static const std::string end_of_str = "0000";

class Multith {
 public:
  Multith(int argc, char *argv[]){
    if (argc == 1) {
      number_threads = std::thread::hardware_concurrency();
    } else {
      number_threads = static_cast<unsigned int>(std::stoi(argv[1]));
    }
    duration = 0;
  }
  ~Multith() {
    for (unsigned int i = 0; i < number_threads; ++i) {
      threads[i].join();
    }
  }

  void static signal_catch(int signum){
    write_to_json_file("logs_0000.json");
    sleep(1);
    std::cout << "\nProgram aborted with code " << --signum << "\n";
    exit(signum);
  }

  void static write_to_json_file(const std::string& file_name){
    std::ofstream output_file;
    std::ifstream input_file;
    output_file.open(file_name);
    input_file.open(file_name);
    json out_json;
    if(input_file.peek() != EOF)
      input_file >> out_json;
    for(auto & right_hash : right_hashs) {
      out_json["values"].push_back(right_hash);
    }
    output_file << out_json.dump(4);
    output_file.close();
  };

  void start(const bool& key);

  void sort_hash(std::string& hash);

  void do_hashing(const bool& key);
 private:
  std::mutex mutex;
  unsigned int number_threads;
  long duration;
  std::string src_str;
  std::string hash_hex_str;
  std::vector<std::thread> threads;
  static std::vector<json> right_hashs;
  boost::log::sources::severity_logger< logging::trivial::severity_level > slg;
};

#endif // INCLUDE_HEADER_HPP_