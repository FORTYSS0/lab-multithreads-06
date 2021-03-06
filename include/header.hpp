// Copyright 2021 by FORTYSS

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <nlohmann/json.hpp>
#include <mutex>
#include <thread>
#include "../PicoSHA2/picosha2.h"
#include <boost/log/trivial.hpp>
#include <boost/thread.hpp>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/program_options.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>

using json = nlohmann::json;

class Multith{
 public:
  Multith(int argc, char *argv[]);
  ~Multith(){
    for(unsigned int i = 0; i < n_thr; ++i) {
      thr[i].join();
    }
  };
  void loger() {
    boost::log::add_file_log(
        boost::log::keywords::file_name = "logs/log_%5N.log",
        boost::log::keywords::rotation_size = 10 * 1024 * 1024,
        boost::log::keywords::time_based_rotation =
            boost::log::sinks::file::rotation_at_time_point(0, 0, 0),
        boost::log::keywords::format =
            "[%TimeStamp%][%Severity%][%ThreadID%]: %Message%");
    };
  std::string hash(std::string src_str){
    std::string hash_hex_str;
    picosha2::hash256_hex_string(src_str, hash_hex_str);
    return hash_hex_str;
  }

 private:
  unsigned int n_thr;
  std::vector<std::thread> thr;
};
#endif // INCLUDE_HEADER_HPP_
