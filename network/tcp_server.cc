/**
 * Copyright (c) 2021, Soul Inc
 * Author: Hongbo Liu <liulu3@soulapp.com>
 * Date  : 2021-12-27 14:58:07
 */

#include <iostream>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

#include "network/addr.h"

void ReadMsg(int fd) {
  const size_t kMaxChar = 4;
  char buf[kMaxChar + 1];
  memset(buf, 0, kMaxChar);
  int len = 0;
  std::cout << "Received Msg:" << std::endl;

  while ((len = read(fd, buf, kMaxChar)) > 0) {
    buf[len] = 0;
    std::cout << buf;

  }
  std::cout << "Msg end!" << std::endl;
}

void EventLoop() {
  int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (sock_fd < 0) {
    std::cout << "Fail to create socket fd" << std::endl;
    return;
  }

  int optval = 1;
  if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) != 0) {
    std::cerr << "Fail to set REUSEADDR option: " << strerror(errno) << std::endl;
    return;
  }

  struct sockaddr_in addr;
  if (!FillIpv4Addr("0.0.0.0", 9090, &addr)) {
    std::cerr << "Fail to fill ipv4 addr info" << std::endl;
    return;
  }

  if (bind(sock_fd, (struct sockaddr*) &addr, sizeof(addr)) != 0) {
    std::cout << "Fail to bind, err: " << strerror(errno) << std::endl;
    return;
  }

  if (listen(sock_fd, SOMAXCONN) != 0) {
    std::cerr << "Fail to listen, errno: " << errno << std::endl;
  }

  while (true) {
    struct sockaddr_in client_addr;
    socklen_t peer_size;
    int conn_fd = accept(sock_fd, (struct sockaddr*)&client_addr, &peer_size);
    if (conn_fd < 0) {
      std::cerr << "Fail to accept, invalid conn fd, err: " << errno << std::endl;
      continue;
    }

    std::cout << "Connection established: fd: " << conn_fd << std::endl;
    ReadMsg(conn_fd);
  }
}

int main(int argc, char *argv[]) {
  std::cout << "PID: " << getpid() << std::endl;
  EventLoop();
  return 0;
}
