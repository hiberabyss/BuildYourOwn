/**
 * Copyright (c) 2021, Soul Inc
 * Author: Hongbo Liu <liulu3@soulapp.com>
 * Date  : 2021-12-27 11:05:55
 */

#include "design_pattern/singleton.h"
#include <iostream>

class A {
public:
  A () {}
  ~A () {}
  void SayHi() {
    std::cout << "Data: " << data << std::endl;
  }

private:
  int data = 10;
};

int main(int argc, char *argv[]) {
  Singleton<A>::GetInstance()->SayHi();
  return 0;
}
