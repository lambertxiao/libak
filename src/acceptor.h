#ifndef LIBAK_ACCEPTOR_H_
#define LIBAK_ACCEPTOR_H_

#include "eventloop.h"
#include "endpoint.h"
#include "socket.h"
#include "net_addr.h"
#include "channel.h"

namespace libak {

using NewConnCB = std::function<void (int sockfd, const NetAddr& peerAddr)> ;

// Acceptor负责在一个NetAddr监听读事件
// 当有连接接入NetAddr时，生成Connection执行回调
class Acceptor {
 public:
  Acceptor(EventLoop* loop, NetAddr addr);

  void listen();
  void set_new_conn_cb(const NewConnCB& cb) { new_conn_cb_ = cb; };
  void handle_read();

 private: 
  NetAddr addr_;
  Socket listen_socket_;
  Channel listen_channel_;
  NewConnCB new_conn_cb_;
};
}

#endif
