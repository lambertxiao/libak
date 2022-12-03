#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <assert.h>

#include <iostream>
#include <fmtlog/fmtlog.h>

#include "channel.h"
#include "channelg/tcp_server.h"

namespace libak {

namespace channelg {

ChannelFD TCPServer::gen(Endpoint ep) {
  int listen_fd = ::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP);
  assert(listen_fd > 0);

  logd("TCPServer listen_fd:{}", listen_fd);

  struct sockaddr_in listen_addr;
  listen_addr.sin_family = AF_INET;
  listen_addr.sin_addr.s_addr = inet_addr(ep.ip.c_str());
  listen_addr.sin_port = htons(ep.port);

  bind(listen_fd, (struct sockaddr *)&listen_addr, sizeof(listen_addr));
	int ret = listen(listen_fd, 10);

  assert(ret == 0);

  return listen_fd;
};
}  // namespace channelg
}  // namespace libak
