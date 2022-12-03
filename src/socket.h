#ifndef LIBAK_SOCKET_H_
#define LIBAK_SOCKET_H_

#include <fmtlog/fmtlog.h>
#include "net_addr.h"

namespace libak {

class Socket {
 public:
  const static int MAX_CONN = 128;

  Socket(sa_family_t family) : 
  sockfd_(::socket(family, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP)) {
    assert(sockfd_ > 0);
  };

  int fd() { return sockfd_; }

  // 绑定地址
  void bind(NetAddr& addr) {
    logd("socket bind");
    int ret = ::bind(sockfd_, addr.addr(), static_cast<socklen_t>(sizeof(struct sockaddr_in)));
    assert(ret == 0);
  }

  // 监听地址
  void listen() {
    logd("socket listen");
    int ret = ::listen(sockfd_, MAX_CONN);
    assert(ret == 0);
  }

  // 接收连接
  void accept(NetAddr& peer) {
    logd("socket accpet");
  }

 private:
  int sockfd_;
};
}  // namespace libak

#endif
