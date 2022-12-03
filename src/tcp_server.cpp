#include <fmtlog/fmtlog.h>

#include "tcp_server.h"
#include "acceptor.h"
#include "net_addr.h"

using namespace std::placeholders;

namespace libak {

TCPServer::TCPServer(EventLoop* loop, NetAddr addr) : loop_(loop), acceptor_(new Acceptor(loop, addr)) {}

void TCPServer::listen() {
  // tcpserver需要关注acceptor的新连接事件
  acceptor_->set_new_conn_cb(std::bind(&TCPServer::new_conn, this, _1, _2));
  acceptor_->listen();
}

void TCPServer::new_conn(int sockfd, const NetAddr& peerAddr) {
  logi("tcp_server new conn comming");
}
}  // namespace libak
