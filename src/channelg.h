#ifndef LIBAK_CHANNEL_GENERATOR_H_
#define LIBAK_CHANNEL_GENERATOR_H_

#include "channel.h"
#include "endpoint.h"

namespace libak {
  
// 负责生成具体的连接，如tcp链接
class ChannelGenerator {
 public:
  virtual Channel* gen(Endpoint ep) = 0;
};
}  // namespace libak
#endif
