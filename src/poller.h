#include <vector>
#include "channel.h"
#include "poller/poller_epoll.h"

namespace libak {

// 找到哪些channel上发生了事件，底层可以基于epoll，poll，kqueue等
class Poller {
 public:
  using ChannelList = std::vector<Channel*>;

  // 在给定的时间内，返回发生事件的channel
  virtual void poll(int timeout_ms, ChannelList* channels) = 0;

  // 在poller中新增，删除，修改channel的关注事件
  virtual void update_channel(Channel* channel) = 0;

  // 在poller中移除channel
  virtual void remove_channel(Channel* channel) = 0;

  static std::unique_ptr<Poller> create_default_poller() {
    return std::make_unique<poller::EpollPoller>();
  }
};

}  // namespace libak
