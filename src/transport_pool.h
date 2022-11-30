#ifndef LIBAK_TRANSPORT_POOL_H_
#define LIBAK_TRANSPORT_POOL_H_

#include "transport.h"
#include "endpoint.h"

namespace libak {

class TransportPool {
 public:
  Transport* get_transport(Endpoint ep, std::string prokey);
};

}  // namespace libak

#endif
