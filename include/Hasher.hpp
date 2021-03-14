// Copyright 2021 by FORTYSS

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <mutex>
#include <boost/log/trivial.hpp>
#include "../third-party/PicoSHA2/picosha2.h"
#include <csignal>
#include <future>
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
#include <nlohmann/json.hpp>
using json = nlohmann::json;
//namespace logging = boost::log;
//namespace src = boost::log::sources;
//namespace sinks = boost::log::sinks;
//namespace keywords = boost::log::keywords;
//namespace po = boost::program_options;

typedef boost::log::sources::severity_logger<boost::log::trivial::severity_level> logger;

class Console {
 private:
  static boost::program_options::options_description desc;
  static std::string fileName;
  static size_t threadsCount;
  class Hasher {
   private:
    static std::vector<json> correctValues;
    static std::mutex mutie;

    [[noreturn]] static void encode(
        std::chrono::time_point<std::chrono::system_clock>& start);
   public:

    static void startHashing();
    static void sigHandler(int signum);
  };
 public:
    void logge() {
        boost::log::add_file_log(
                boost::log::keywords::file_name = "logs/log_%5N.log",
                boost::log::keywords::rotation_size = 10 * 1024 * 1024,
                boost::log::keywords::time_based_rotation =
                        boost::log::sinks::file::rotation_at_time_point(0, 0, 0),
                boost::log::keywords::format = "[%TimeStamp%][%Severity%][%ThreadID%]: %Message%");

        srand(time(nullptr));
    }
  static int wmain(const boost::program_options::variables_map& vm);
  Console();
    boost::program_options::options_description& getDesc() const{ return desc; }
};

#endif // INCLUDE_HEADER_HPP_
