/**
 * Copyright (c) 2021, Soul Inc
 * Author: Hongbo Liu <liulu3@soulapp.com>
 * Date  : 2021-12-27 16:58:10
 */

#include <iostream>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>

#include "network/addr.h"

char* Readline(size_t* cnt) {
  char* line = nullptr;
  if (getline(&line, cnt, stdin) < 0) {
    if (feof(stdin)) {
      exit(0);
    }
    std::cerr << "Fail to read line, err: " << strerror(errno) << std::endl;
  }

  return line;
}

bool DoConnect() {
  int sfd = socket(AF_INET, SOCK_STREAM, 0);
  sockaddr_in addr;
  if (!FillIpv4Addr("127.0.0.1", 9090, &addr)) {
    std::cerr << "Fail to fill ipv4 addr" << std::endl;
    return false;
  }

  if (connect(sfd, (struct sockaddr*)&addr, sizeof(sockaddr_in)) != 0) {
    std::cerr << "Fail to connect: err: " << strerror(errno) << std::endl;
    return false;
  }
  std::cout << "Connect to server succefully!" << std::endl;

  while (true) {
    std::cout << "Input Msg> ";
    size_t line_size = 0;
    auto* line = Readline(&line_size);
    if (write(sfd, (void*)line, line_size) < 0) {
      std::cerr << "Fail to write msg" << std::endl;
    }

    std::cout << line;

    free(line);
  }
  return true;
}

int main(int argc, char *argv[]) {
  if (!DoConnect()) {
    std::cerr << "Fail to connect server" << std::endl;
  }
  return 0;
}
