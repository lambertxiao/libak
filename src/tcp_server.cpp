#include <fmtlog/fmtlog.h>

#include "tcp_server.h"
#include "tcp_conn.h"
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
  // 收到连接后，封装成TcpConn，并丢入io_loop中
  auto conn = new TCPConn(sockfd);
  // 丢入loop执行
  loop_->run_in_loop(std::bind(&TCPConn::on_connected, conn));
}
}  // namespace libak
