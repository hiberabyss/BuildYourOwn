/**
 * Copyright (c) 2021, Soul Inc
 * Author: Hongbo Liu <liulu3@soulapp.com>
 * Date  : 2021-12-27 17:21:37
 */

#ifndef ADDR_H_BHPJ9KS2
#define ADDR_H_BHPJ9KS2

#include <iostream>
#include <netinet/ip.h>
#include <arpa/inet.h>

bool FillIpv4Addr(const std::string& ip, uint16_t port,
                  struct sockaddr_in* addr) {
  addr->sin_family = AF_INET;
  addr->sin_port = htons(port);
  if (inet_pton(AF_INET, ip.c_str(), &addr->sin_addr) != 1) {
    std::cerr << "Fail to convert ip address" << std::endl;
    return false;
  }

  return true;
}

#endif /* end of include guard: ADDR_H_BHPJ9KS2 */
