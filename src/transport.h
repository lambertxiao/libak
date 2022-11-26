#ifndef LIBAK_TANSPORT_H_
#define LIBAK_TANSPORT_H_

#include "libak.h"

namespace libak {
  
// Transport 代表两端之间通过proto建立的桥梁
class Transport {
 public:
  Proto proto;
  Endpoint ep;

  template <typename Msg>
  void send(Msg msg);
};
}

#endif
