#include <string>

#include "libak.h"

struct HelloMsg {
  std::string op_type;
  std::string name;
};

class HelloMsgEnDecoder : public libak::MsgEnDecoder {
 public:
  template <typename Msg>
  libak::EncMsg* encode_msg(Msg& msg) {
    HelloMsg _msg = static_cast<HelloMsg>(msg);

    auto content = "op_type:" + _msg.op_type + ",name=" + _msg.name;
    auto buf = new libak::ByteData(&content[0], content.size());

    auto enc_msg = new libak::EncMsg();
    enc_msg->msg_id = "xxxxxx";
    enc_msg->payload = buf;

    return enc_msg;
  }
};

int main() {
  auto edr = new HelloMsgEnDecoder();
  auto cg = new libak::TCPConnGenerator();

  auto proto_key = "hellotp";
  libak::Proto proto = {
    .key = proto_key, 
    .edr = edr, 
    .cg = cg,
  };

  libak::ProtoCenter::regist_proto(proto);

  libak::Endpoint ep = {
    .ip = "127.0.0.1",
    .port = 3000,
  };

  HelloMsg hello_msg = {
    .op_type = "op_test",
    .name = "hello",
  };

  auto client = new libak::Client();
  client->send<HelloMsg>(ep, proto_key, hello_msg);
}