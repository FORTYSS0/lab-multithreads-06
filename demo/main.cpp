// Copyright 2021 by FORTYSS
#include "Hasher.hpp"




boost::program_options::options_description Console::desc("Allowed options");

int main(int argc, char** argv) {
  Console console;
  console.logge();
    boost::program_options::variables_map vm;
    boost::program_options::parsed_options parsed = boost::program_options::command_line_parser(argc, argv)
      .options(console.getDesc())
      .allow_unregistered()
      .run();
    boost::program_options::store(parsed, vm);
    boost::program_options::notify(vm);


  Console::wmain(vm);
}
