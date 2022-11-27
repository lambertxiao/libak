#ifndef LIBAK_TRANSPORT_H_
#define LIBAK_TRANSPORT_H_

#include "proto.h"
#include "conn.h"
#include "msg_queue.h"

namespace libak {
  
class Transport {
 public:
  Proto* proto;
  Connection* conn;
  MsgQueue *mq;

  Transport(Proto* proto, Connection* conn) {
    this->proto = proto;
    this->conn = conn;
  };

  template <typename Msg>
  void send(Msg msg);
};
}

#endif
