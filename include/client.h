#ifndef LIBAK_CLIENT_H_
#define LIBAK_CLIENT_H_

#include "transport.h"
#include "transport_pool.h"

namespace libak {

class Client {
 public:
  void* send(Endpoint ep, std::string prokey, void* msg);

 private:
  TransportPool* transport_pool;
};
}  // namespace libak

#endif
