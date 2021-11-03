#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <thread>

using namespace std;

void DoCount(const string& name) {
  // each thread has a copy
  thread_local int cnt = 0;
  cnt++;

  std::cout << name << ": " << cnt << std::endl;
}

void ThreadFun(const string& name) {
  for (int i = 0; i < 4; ++i) {
    DoCount(name);
  }
}

int main(int argc, char *argv[]) {
  thread t1(ThreadFun, "t1");
  t1.join();

  thread t2(ThreadFun, "t2");
  t2.join();

  return 0;
}
