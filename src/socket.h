#ifndef LIBAK_SOCKET_H_
#define LIBAK_SOCKET_H_

#include <fmtlog/fmtlog.h>

#include "net_addr.h"

namespace libak {

class Socket {
 public:
  const static int MAX_CONN = 128;

  Socket(sa_family_t family) : sockfd_(::socket(family, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP)) {
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
  int accept(sockaddr_in* addr) {
    logd("socket accpet");
    socklen_t addrlen = static_cast<socklen_t>(sizeof addr);
    int connfd = ::accept4(sockfd_, (sockaddr*)addr, &addrlen, SOCK_NONBLOCK | SOCK_CLOEXEC);

    if (connfd < 0) {
      int savedErrno = errno;
      loge("socket accept error");
      switch (savedErrno) {
        case EAGAIN:
        case ECONNABORTED:
        case EINTR:
        case EPROTO:  // ???
        case EPERM:
        case EMFILE:  // per-process lmit of open file desctiptor ???
          // expected errors
          errno = savedErrno;
          break;
        case EBADF:
        case EFAULT:
        case EINVAL:
        case ENFILE:
        case ENOBUFS:
        case ENOMEM:
        case ENOTSOCK:
        case EOPNOTSUPP:
          // unexpected errors
          loge("unexpected error of ::accept {}", savedErrno);
          break;
        default:
          loge("unknown error of ::accept {}", savedErrno);
          break;
      }
    }
    return connfd;
  }

 private:
  int sockfd_;
};
}  // namespace libak

#endif
