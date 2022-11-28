#ifndef LIBAK_CLIENT_H_
#define LIBAK_CLIENT_H_


#include "transport.h"
#include "transport_pool.h"
#include "eventloop.h"

namespace libak {

class Client {
 public:
  Client() {}
  void* send(Endpoint ep, std::string prokey, void* msg);

 private:
  TransportPool* transport_pool;
  EventLoop eventloop;
};
}  // namespace libak

#endif
