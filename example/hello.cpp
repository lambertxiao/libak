#include <iostream>
#include <string>

#include "libak.h"

struct HelloMsg {
  std::string op_type;
  std::string name;
};

class HelloMsgEnDecoder : public libak::MsgEnDecoder {
 public:
  libak::EncMsg encode_msg(void* msg) override {
    HelloMsg* _msg = static_cast<HelloMsg*>(msg);

    auto content = "op_type:" + _msg->op_type + ",name=" + _msg->name;
    auto buf = new libak::ByteData(&content[0], content.size());

    libak::EncMsg enc_msg;
    enc_msg.msg_id = "xxxxxx";
    enc_msg.payload = buf;

    return enc_msg;
  }
};

int main() {
  auto proto_key = "hellotp";
  auto edr = new HelloMsgEnDecoder();
  auto cg = new libak::TCPConnGenerator();
  auto proto = new libak::Proto(proto_key, edr, cg);

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
  client->send(ep, proto_key, &hello_msg);
}
