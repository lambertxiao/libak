#ifndef LIBAK_TRANSPORT_POOL_H_
#define LIBAK_TRANSPORT_POOL_H_

#include "endpoint.h"
#include "transport.h"

namespace libak {

class TransportPool {
 public:
  Transport* get_transport(Endpoint ep, std::string prokey);
};

}  // namespace libak

#endif
