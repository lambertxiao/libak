#include <string>

#include "libak.h"
#include "endpoint.h"
#include "client.h"
#include "proto.h"

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

  auto proto_key = "hellotp";
  libak::Proto proto = {
    .key = proto_key, 
    .msg_en_decoder = edc, 
  };

  libak::ProtoCenter::regist_proto(proto);

  libak::Endpoint ep = {
    .ip = "127.0.0.1",
    .port = 3000,
  };
  HelloMsg hello_msg;

  libak::Client* client;
  client->send<HelloMsg>(ep, proto_key, hello_msg);
}
