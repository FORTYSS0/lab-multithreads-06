// Copyright 2020 Your Name <your_email>

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
#include <nlohmann/json.hpp>
using json = nlohmann::json;



namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;

typedef src::severity_logger< logging::trivial::severity_level > logger;


[[noreturn]] void encode(
    std::vector<json>& CorrectValues, std::chrono::time_point< std::chrono::system_clock > & start);

#endif // INCLUDE_HEADER_HPP_
