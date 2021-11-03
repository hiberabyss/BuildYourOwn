/**
 * Copyright (c) 2021, Soul Inc
 * Author: Hongbo Liu <liulu3@soulapp.com>
 * Date  : 2021-10-27 16:34:14
 */

#include <future>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

string Job1(const string& name) {
  this_thread::sleep_for(3s);

  return "Job1 finished!";
}

int Job2() {
  this_thread::sleep_for(2s);
  return 100;
}

int main(int argc, char *argv[]) {
  auto job1 = async(Job1, "Input");
  auto job2 = async(Job2);

  std::cout << job1.get() << std::endl;
  std::cout << job2.get() << std::endl;

  return 0;
}
