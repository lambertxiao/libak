#ifndef LIBAK_TRANSPORT_POOL_H
#define LIBAK_TRANSPORT_POOL_H

#include "libak.h"
#include "transport.h"

namespace libak {

class TransportPool {
 public:
  Transport* get_transport(Endpoint ep, std::string prokey);
};

}  // namespace libak

#endif
