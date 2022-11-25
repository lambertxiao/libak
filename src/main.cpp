#include <string>

#include "libak.h"
#include "libak_client.h"
#include "transport_tcp.h"

struct HelloMsg {
  std::string op_type;
  std::string field1;
  uint32_t field2;
  char* field3;
  char* field3_len;
};

class HelloMsgEnDecoder : public libak::MsgEnDecoder {
 public:
  void encode_msg(){};
  void decode_msg(){};
};

int main() {
  HelloMsgEnDecoder* edc = new HelloMsgEnDecoder();
  libak::TCPTransport* tcpp = new libak::TCPTransport();

  libak::RoundTripper rt = {
      .key = "helloak",
      .msg_en_decoder = edc,
      .transport = tcpp,
  };

  libak::RTCenter::regist_rt(rt);

  libak::Client* client;

  std::string rt_key = "hello";
  client->regist_rt(rt_key, rt);

  libak::Endpoint ep = {
      .ip = "127.0.0.1",
      .port = 3000,
  };

  HelloMsg hello_msg;
  client->send<HelloMsg>(ep, rt_key, hello_msg);
}
