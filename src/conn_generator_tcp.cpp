#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>

#include "libak.h"

namespace libak {

Connection* TCPConnGenerator::gen(Endpoint ep) {
  int clientfd = socket(AF_INET, SOCK_STREAM, 0);
  if (clientfd == -1) {
    std::cout << "create client socket error" << std::endl;
    throw "create client socket error";
  }

  struct sockaddr_in serveraddr;
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = inet_addr(ep.ip.c_str());
  serveraddr.sin_port = htons(ep.port);

  if (connect(clientfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) == -1) {
    std::cout << "connect socket error" << std::endl;
    throw "connect socket error";
  }

  return new Connection(clientfd);
}
}  // namespace libak
