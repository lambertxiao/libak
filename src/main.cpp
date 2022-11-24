#include <string>
#include "libak.h"

struct HelloMsg {
  std::string msg;
};

int main() { 
  libak::Client* client;

  std::string rt_key = "hello";
  libak::RoundTripper rt;
  client->registRT(rt_key, rt);


  libak::Endpoint ep = {
    .ip = "127.0.0.1", 
    .port = 3000,
  };

  HelloMsg hello_msg = {.msg = "hello yo"};
  client->send(ep, rt_key, &hello_msg, sizeof(hello_msg));
}
