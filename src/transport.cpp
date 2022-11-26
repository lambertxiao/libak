#include "transport.h"
#include "msg_queue.h"

namespace libak {

template <typename Msg>
void Transport::send(Msg msg) {
  auto msg_data = proto->msg_en_decoder->encode_msg(msg);
  mq->enqueue<EncodedMsg*>(msg_data);
}
}
