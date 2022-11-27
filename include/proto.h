#ifndef LIBAK_PROTO_H_
#define LIBAK_PROTO_H_

#include <string>
#include <functional>

#include "conn_generator.h"
#include "msg_en_decoder.h"

namespace libak {

// 代表传输契约
class Proto {
 public:
  std::string key;
  MsgEnDecoder* edr;
  ConnGenerator* cg;

  Proto(std::string key, MsgEnDecoder* edr, ConnGenerator* cg) {
    this->key = key;
    this->edr = edr;
    this->cg = cg;
  }
};
}  // namespace libak

#endif
