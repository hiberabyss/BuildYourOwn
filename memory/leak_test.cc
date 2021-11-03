/**
 * Copyright (c) 2021, Soul Inc
 * Author: Hongbo Liu <liulu3@soulapp.com>
 * Date  : 2021-11-03 20:34:59
 */

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <thread>
#include <unistd.h>

// Check with: while true; do ( pmap -d <#pid> | tail -1; sleep 1) done

using namespace std;

void DoLeak() {
  int i = 0;

  while (true) {
    i++;
    // void* pint = malloc(1024 * 1024);
    void* pint = malloc(1024 * 1024);

    *((int*)pint) = i;
    std::cout << "PID: " << getpid() << " " << *(int*)pint << std::endl;
    this_thread::sleep_for(100ms);
  }
}

int main(int argc, char *argv[]) {
  DoLeak();
  return 0;
}
