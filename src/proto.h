#ifndef LIBAK_PROTO_H_
#define LIBAK_PROTO_H_

#include <string>

#include "conn_generator.h"
#include "msg_en_decoder.h"

namespace libak {

// 代表传输契约
class Proto {
 public:
  std::string key;
  MsgEnDecoder* edr;
  ConnGenerator* cg;
};
}  // namespace libak

#endif
