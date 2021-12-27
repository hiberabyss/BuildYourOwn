/**
 * Copyright (c) 2021, Soul Inc
 * Author: Hongbo Liu <liulu3@soulapp.com>
 * Date  : 2021-11-17 15:31:44
 */

#include <unistd.h>
#include <signal.h>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void sig_handler(int sig) {
  std::cout << "Sig handled: " << sig << std::endl;
}

int main(int argc, char *argv[]) {
  std::cout << "Begin sleep, pid: " << getpid() << std::endl;
  signal(SIGINT, sig_handler);

  int left = sleep(100);

  std::cout << "Still has seconds left: " << left << std::endl;
  return 0;
}
