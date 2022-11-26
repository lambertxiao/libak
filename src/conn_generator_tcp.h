#ifndef LIBAK_CONN_GENERATOR_TCP_H_
#define LIBAK_CONN_GENERATOR_TCP_H_

#include "conn.h"
#include "conn_generator.h"

namespace libak {
class TCPConnGenerator : public ConnGenerator {
 public:
  Connection* gen(Endpoint ep) override;
};
}  // namespace libak
#endif
