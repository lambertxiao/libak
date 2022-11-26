#include <string>

namespace libak {
class ByteData {
  char* addr;
  uint32_t len;
};

class EncodedMsg {
  std::string msg_id;
  ByteData* payload;
};

class MsgEnDecoder {
 public:

  template <typename Msg>
  EncodedMsg* encode_msg(Msg msg);

  // template <typename Msg>
  // EncodedMsg decode_msg(ByteData* payload);
};
}  // namespace libak
