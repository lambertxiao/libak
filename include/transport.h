#ifndef LIBAK_TRANSPORT_H_
#define LIBAK_TRANSPORT_H_

#include "proto.h"
#include "channel.h"
#include "msg_queue.h"

namespace libak {
  
class Transport {
 public:
  Proto* proto;
  Channel* channel;
  MsgQueue *mq;

  Transport(Proto* proto, Channel* channel) {
    this->proto = proto;
    this->channel = channel;
  };

  void send(void* msg);
};
}

#endif
