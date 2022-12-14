#include "acceptor.h"

#include <fmtlog/fmtlog.h>

#include "net_addr.h"
#include "socket.h"

namespace libak {

Acceptor::Acceptor(EventLoop* loop, NetAddr addr)
    : addr_(addr), 
      listen_socket_(addr.family()), // 创建好nonblocking的socket
      listen_channel_(loop, listen_socket_.fd()) // listen_channel关注listen_socket的fd
{
  // 绑定地址
  listen_socket_.bind(addr);
  // 设置有数据时的回调
  listen_channel_.set_read_cb(std::bind(&Acceptor::handle_read, this));
};

void Acceptor::listen() {
  logi("acceptor({}) start listening at {}:{}", listen_socket_.fd(), addr_.ip(), addr_.port());
  listen_socket_.listen();
  listen_channel_.watch_read();
};

// 在handle_read中产生新连接
void Acceptor::handle_read() {
  sockaddr_in addr;
  int conn_fd = listen_socket_.accept(&addr);

  if (conn_fd >= 0) {
    NetAddr peer_addr(addr);
    new_conn_cb_(conn_fd, peer_addr);
  } else {
    loge("accpet error, conn_fd:{}", conn_fd);
  }
}

}  // namespace libak
