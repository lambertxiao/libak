#include "conn.h"

#include <sys/socket.h>
#include <iostream>

namespace libak {

const int MSG_ID_HEAD_SIZE = 50;

void Connection::write(EncMsg& msg) {
  // msg_id为80字节
  // 
  auto head_buf = malloc(MSG_ID_HEAD_SIZE*sizeof(char*));
  std::cout << sizeof(msg.msg_id) << std::endl;
  std::cout << msg.payload->len << std::endl;

  // auto buf = malloc();

  // int ret = send(socket_fd, msg, strlen(SEND_DATA), 0);
  // if (ret != strlen(SEND_DATA)) {
  //   return -1;
  // }
};
}  // namespace libak
