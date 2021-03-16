// Copyright 2021 by FORTYSS
#include <multithread.hpp>


int main(int argc, char *argv[]) {
  signal(SIGINT, Multith::signal_catch);
  Multith hasher(argc, argv);
  hasher.start(true);
}
