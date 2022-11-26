#ifndef LIBAK_PROTO_H_
#define LIBAK_PROTO_H_

#include <string>

#include "conn_generator.h"
#include "msg_en_decoder.h"

namespace libak {

// 负责把msg从一端传输到另一端，
class Proto {
 public:
  std::string key;
  // 负责对消息进行格式的编码转码
  MsgEnDecoder* msg_en_decoder;
  // 负责生成具体的连接，如tcp链接
  ConnGenerator cg;
};
}  // namespace libak

#endif
