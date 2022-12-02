#ifndef LIBAK_TRANSPORT_H_
#define LIBAK_TRANSPORT_H_

#include "channel.h"
#include "msg_queue.h"
#include "proto.h"

namespace libak {

class Transport {
 public:
  Proto* proto_;
  Channel* ch_;
  MsgQueue* mq;

  Transport(Proto* proto, Channel* ch) : proto_(proto), ch_(ch){};

  void send(void* msg);
};
}  // namespace libak

#endif
