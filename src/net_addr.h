#ifndef LIBAK_INET_ADDR_H_
#define LIBAK_INET_ADDR_H_

#include <arpa/inet.h>
#include <fmtlog/fmtlog.h>
#include <netinet/in.h>
#include <memory>
#include <string>

namespace libak {
class NetAddr {
 public:
  NetAddr() {};
  NetAddr(std::string ip, uint16_t port, bool ipv6 = false) {
    if (!ipv6) {
      addr_.sin_family = AF_INET;
      addr_.sin_port = htons(port);
      addr_.sin_addr.s_addr = inet_addr(ip.c_str());
    }
  };

  NetAddr(sockaddr_in addr): addr_(addr) {};

  sa_family_t family() const { return addr_.sin_family; }
  std::string ip() { return inet_ntoa(addr_.sin_addr); }
  uint16_t port() { return ntohs(addr_.sin_port); }

  sockaddr* addr() { 
    return (struct sockaddr *)&addr_;
  } 

 private:
  union {
    struct sockaddr_in addr_;
    struct sockaddr_in6 addr6_;
  };
};

}  // namespace libak

#endif
