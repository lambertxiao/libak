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
  std::string msg_id;
  ByteData* payload;
};

// 负责对消息进行格式的编码转码
class MsgEnDecoder {
 public:
  template <typename Msg>
  EncMsg* encode_msg(Msg& msg);

  // template <typename Msg>
  // EncodedMsg decode_msg(ByteData* payload);
};
}  // namespace libak

#endif
