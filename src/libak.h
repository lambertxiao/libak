#ifndef LAMBERTX_LIBAK_H_
#define LAMBERTX_LIBAK_H_

#include <string>

namespace libak {

// 传输内容的拆包分包, 由业务上来实现
class MsgEnDecoder {
 public:
  virtual void encode_msg() = 0;
  virtual void decode_msg() = 0;
};

// 由库来提供常见的传输协议实现，tcp, udp
class PacketEnDecoder {
 public:
  virtual void encode_packet() = 0;
  virtual void decode_packet() = 0;
};

class RoundTripper {
  MsgEnDecoder* msg_en_decoder;
  PacketEnDecoder* packet_en_decoder;
};

struct Endpoint {
  std::string ip;
  uint32_t port;
};

class Client {
 public:
  virtual void send(Endpoint ep, std::string rt_key, void* msg, uint32_t len) = 0;
  virtual void registRT(std::string key, RoundTripper rt);
};

}  // namespace libak
#endif
