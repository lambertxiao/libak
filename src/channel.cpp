#include "channel.h"

#include <string.h>
#include <sys/socket.h>

#include <iostream>

namespace libak {

void Channel::write(void *data, int data_len) {
  // [size, ...data...]
  // head里只有一个int值，存放着body size
  auto head_size = sizeof(int);
  auto buf_len = head_size + sizeof(char *) * data_len;
  auto buf = (char *)malloc(buf_len);
  memcpy(buf, &data_len, sizeof(int));
  memcpy(buf + head_size, data, data_len);

  auto ret = send(socket_fd, buf, buf_len, 0);
  if (ret != buf_len) {
    std::cout << "send buf failed, sent: " << buf_len << " ret: " << ret << std::endl;
  }
};
}  // namespace libak
