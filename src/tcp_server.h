#ifndef LIBAK_TCP_SERVER_H_
#define LIBAK_TCP_SERVER_H_

#include "common/noncopyable.h"
#include "net_addr.h"
#include "eventloop.h"
#include "acceptor.h"

namespace libak {
class TCPServer : common::noncopyable {
 public:
  TCPServer(EventLoop* loop, NetAddr addr);
  void listen();

 private:
  // 这个loop负责连接接入
  EventLoop* loop_;

  // acceptor负责listen以及accept
  std::unique_ptr<Acceptor> acceptor_;

  // 当有新连接产生时调用
  void new_conn(int sockfd, const NetAddr& peerAddr);
};
}  // namespace libak

#endif
