#include "libak.h"

int main() {
  libak::set_log_level();
  libak::EventLoop loop;
  libak::NetAddr addr("127.0.0.1", 8080, false);
  libak::TCPServer server(&loop, addr);
  server.listen();
  loop.start_loop();
}
