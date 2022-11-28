#ifndef LIBAK_CONN_GENERATOR_TCP_H_
#define LIBAK_CONN_GENERATOR_TCP_H_

#include "channel.h"
#include "channel_generator.h"

namespace libak {
class TCPConnGenerator : public ConnGenerator {
 public:
  Channel* gen(Endpoint ep) override;
};
}  // namespace libak
#endif
