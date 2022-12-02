#ifndef LIBAK_SERVER_H_
#define LIBAK_SERVER_H_

#include <assert.h>
#include <sys/socket.h>

#include "endpoint.h"
#include "eventloop.h"
#include "proto.h"

namespace libak {

void Listen(Proto proto, Endpoint ep) {
  assert(proto.cg_ != NULL);
  auto fd = proto.cg_->gen(ep);
  assert(fd != 0);

  libak::EventLoop loop;
  Channel c(&loop, fd);
  loop.start_loop();
}

}  // namespace libak

#endif
