#ifndef LIBAK_CHG_TCP_H_
#define LIBAK_CHG_TCP_H_

#include "channel.h"
#include "channelg.h"

namespace libak {
namespace channelg {

class TCPClientCHG : public ChannelGenerator {
 public:
  ChannelFD gen(Endpoint ep) override;
};
}  // namespace channelg
}  // namespace libak
#endif
