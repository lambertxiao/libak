#include <vector>

#include "channel.h"

namespace libak {

// 找到哪些channel上发生了事件，底层可以基于epoll，poll，kqueue等
class Poller {
 public:
  using ChannelList = std::vector<Channel*>;

  /// Polls the I/O events.
  /// Must be called in the loop thread.
  virtual void poll(int timeoutMs, ChannelList* activeChannels) = 0;
};

}  // namespace libak
