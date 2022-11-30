#ifndef LIBAK_MSG_ENDECODER_H_
#define LIBAK_MSG_ENDECODER_H_
#include <string>

namespace libak {
class ByteData {
 public:
  char* addr;
  uint32_t len;

  ByteData(char* addr, uint32_t len) {
    this->addr = addr;
    this->len = len;
  };
};

class EncMsg {
 public:
  std::string msg_id;
  ByteData* payload;
};

class MsgEnDecoder {
 public:
  // 消息编码
  virtual EncMsg encode_msg(void* msg) = 0;
};
}  // namespace libak

#endif
