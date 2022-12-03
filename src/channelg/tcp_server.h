#ifndef LIBAK_CHG_TCP_SERVER_H_
#define LIBAK_CHG_TCP_SERVER_H_

#include "channel.h"
#include "channelg.h"

namespace libak {
namespace channelg {

class TCPServer : public ChannelGenerator {
 public:
  ChannelFD gen(Endpoint ep) override;
};
}  // namespace channelg
}  // namespace libak
#endif
