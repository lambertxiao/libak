#ifndef LIBAK_MSGQUEUE_H_
#define LIBAK_MSGQUEUE_H_

namespace libak {

class MsgQueue {
 public:
 template <typename Msg>
  void enqueue(Msg msg);
};
}
#endif
