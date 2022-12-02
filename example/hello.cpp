#include "libak.h"

int main() {
  libak::channelg::TCPServerCHG cg;

  auto proto = libak::Proto{
    .key_ = "hello-server", 
    .edr_ = NULL, 
    .cg_= &cg,
  };

  auto ep = libak::Endpoint{
    .ip = "127.0.0.1",
    .port = 8080,
  };

  libak::Listen(proto, ep);
}
