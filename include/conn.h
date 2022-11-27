#ifndef LIBAK_CONN_H_
#define LIBAK_CONN_H_

#include <stdint.h>

#include "msg_en_decoder.h"

namespace libak {

// Connection是一个逻辑上的通道，可读可写
class Connection {
 public:
  Connection(int socket_fd) { this->socket_fd = socket_fd; }

  void write(EncMsg& msg);

 private:
  int socket_fd;
};

}  // namespace libak
#endif
