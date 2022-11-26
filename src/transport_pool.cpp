#include "libak.h"
#include "transport.h"
#include "endpoint.h"
#include "transport_pool.h"

namespace libak {

Transport* TransportPool::get_transport(Endpoint ep, std::string prokey) {
  auto proto = libak::ProtoCenter::get_proto(prokey);
  auto conn = proto->cg.gen(ep);
  return new Transport(proto, conn);;
};
}
