#ifndef LIBAK_TRANSPORT_H_
#define LIBAK_TRANSPORT_H_

#include "libak.h"
#include "conn.h"
#include "msg_queue.h"

namespace libak {
  
// Transport 代表两端之间通过proto建立的桥梁
class Transport {
 public:
  Proto* proto;
  Connection* conn;
  MsgQueue *mq;

  Transport(Proto* proto, Connection* conn) {
    this->proto = proto;
    this->conn = conn;
  }

  template <typename Msg>
  void send(Msg msg);
};
}

#endif
