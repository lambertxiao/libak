#include "transport.h"
#include "msg_queue.h"

namespace libak {

template <typename Msg>
void Transport::send(Msg msg) {
  auto msg_data = proto->edr->encode_msg(msg);
  conn->write(msg_data);
}
}
