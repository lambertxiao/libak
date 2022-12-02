#ifndef LIBAK_CHG_H_
#define LIBAK_CHG_H_

#include "channel.h"
#include "endpoint.h"

namespace libak {

using ChannelFD = int;
  
// 负责生成具体的连接，如tcp链接
class ChannelGenerator {
 public:
  virtual ChannelFD gen(Endpoint ep) = 0;
};
}  // namespace libak
#endif
