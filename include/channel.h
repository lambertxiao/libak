#ifndef LIBAK_CONN_H_
#define LIBAK_CONN_H_

#include <stdint.h>

#include "msg_en_decoder.h"

namespace libak {

// Channel是一个逻辑上的通道，可读可写
class Channel {
 public:
  Channel(int socket_fd) { this->socket_fd = socket_fd; }
  void write(void* data, int data_len);
  void handle_event();
  void set_receive_events(int revt) { revents_ = revt; } // used by pollers

 private:
  int socket_fd;
  int revents_;
};

}  // namespace libak
#endif
