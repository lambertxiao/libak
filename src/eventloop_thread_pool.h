#ifndef LIBAK_EVENTLOOP_THREAD_POOL_H_
#define LIBAK_EVENTLOOP_THREAD_POOL_H_

#include <memory>
#include <vector>
#include "eventloop.h"
#include "eventloop_thread.h"

namespace libak {

class EventLoopThreadPool {
 public:
  EventLoop* next();
 private:
  std::vector<std::unique_ptr<EventLoopThread>> threads_;
  
};

}  // namespace libak

#endif
