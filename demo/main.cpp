// Copyright 2021 by FORTYSS
#include <multithread.hpp>


int main(int argc, char *argv[]) {
  signal(SIGINT, Multith::catch_signal);
  Multith hasher(argc, argv);
  hasher.start();
}
