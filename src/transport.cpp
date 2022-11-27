#include <iostream>
#include "transport.h"
#include "msg_queue.h"

namespace libak {

void Transport::send(void* msg) {
  auto msg_data = proto->edr->encode_msg(msg);
  std::cout << "write data to conn, msg_id: " << msg_data.msg_id << std::endl;
  conn->write(msg_data.payload->addr, msg_data.payload->len);
};

}
