/**
 * Copyright (c) 2022, Soul Inc
 * Author: Hongbo Liu <liulu3@soulapp.com>
 * Date  : 2022-01-19 20:04:52
 */

#include <iostream>

#include "linux/list.h"

struct MyData {
  int data = 0;
  struct list_head mylst;
  MyData(int v) : data(v) {}
};

void TestLst() {
  LIST_HEAD(my_list);

  MyData* first = nullptr;

  for (int i = 1; i <= 5; ++i) {
    auto tmp = new MyData(i);
    list_add(&tmp->mylst, &my_list);
  }

  MyData* pos;
  list_for_each_entry(pos, &my_list, mylst) {
    std::cout << pos->data << std::endl;
  }
}

int main(int argc, char *argv[]) {
  TestLst();
  return 0;
}
