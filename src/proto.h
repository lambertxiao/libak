#ifndef LIBAK_PROTO_H_
#define LIBAK_PROTO_H_

#include <functional>
#include <string>

#include "channelg.h"
#include "msg_en_decoder.h"

namespace libak {

// 代表传输契约
struct Proto {
  std::string key_;
  MsgEnDecoder* edr_;
  ChannelGenerator* cg_;
};
}  // namespace libak

#endif
