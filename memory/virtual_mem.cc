#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <sys/mman.h>
#include <unistd.h>

using namespace std;

void do_mmap() {
  char* p = (char*)mmap(nullptr, 4096 + 1, PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  if (p == MAP_FAILED) {
    cerr << "Fail to mmap";
    return;
  }

  std::cout << "PID: " << getpid() << std::endl;

  *p = 12;
  printf("Page 1 pointer: %p\n", p);
  sleep(10);

  p += 4096;
  *p = 34;
  printf("Page 2 pointer: %p\n", p);
  sleep(10);
}

int main(int argc, char *argv[]) {
  do_mmap();
  return 0;
}
