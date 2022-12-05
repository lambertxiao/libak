#ifndef LIBAK_TCP_CONN_H_
#define LIBAK_TCP_CONN_H_

#include "buffer.h"
#include "eventloop.h"

namespace libak {

class TCPConn {
 public:
  TCPConn(EventLoop* ioloop, int sockfd) : sockfd_(sockfd) {}
  void on_connected();

 private:
  // 只负责管理conn上的io事件
  EventLoop ioloop_;
  int sockfd_;

  // 写缓冲区
  Buffer w_buf_;
  // 读缓冲区
  Buffer r_buf_;

  void handle_read();
  void handle_write();
};
}

#endif
