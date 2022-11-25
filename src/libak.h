#ifndef LAMBERTX_LIBAK_H_
#define LAMBERTX_LIBAK_H_

#include <string>

namespace libak {

class RTCenter {
 public:
  static void regist_rt(RoundTripper rt) { return; };
};

// 传输内容的拆包分包, 由业务上来实现
class MsgEnDecoder {
 public:
  virtual void encode_msg() = 0;
  virtual void decode_msg() = 0;
};

// 由库来提供常见的传输协议实现，tcp, udp

// 负责把msg从一端传输到另一端，对上屏蔽掉消息封包的过程以及使用什么传输协议
class RoundTripper {
 public:
  std::string key;
  MsgEnDecoder* msg_en_decoder;
  Transport* transport;
};

struct Endpoint {
  std::string ip;
  uint32_t port;
};

class Callback {};

}  // namespace libak
#endif
