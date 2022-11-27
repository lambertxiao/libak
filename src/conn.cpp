#include "conn.h"

#include <sys/socket.h>
#include <iostream>

namespace libak {

void Connection::write(void *data, int data_len) {
  // 先发送一个int代表整个包的长度
  auto ret = send(socket_fd, &data_len, sizeof(data_len), 0);
  // 再发送payload部分
  ret = send(socket_fd, data, data_len, 0);
};
}  // namespace libak
