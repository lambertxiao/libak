#ifndef LIBAK_ENDPOINT_H_
#define LIBAK_ENDPOINT_H_

#include <string>

namespace libak {

struct Endpoint {
  std::string ip;
  uint32_t port;
};

}
#endif
