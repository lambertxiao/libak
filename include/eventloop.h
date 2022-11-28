#include <sys/epoll.h>
#include <functional>

namespace libak {

class EventLoop {
 public:
  void subscibeFDEvent(int fd, int event, std::function<void(void*)>);
};
 
}  // namespace libak
