#ifndef LIBAK_POLLER_H_
#define LIBAK_POLLER_H_

#include <vector>
#include <memory>
#include "channel.h"

namespace libak {

class Channel;

// 找到哪些channel上发生了事件，底层可以基于epoll，poll，kqueue等
class Poller {
 public:
  typedef std::vector<Channel*> ChannelList;

  // 在给定的时间内，返回发生事件的channel
  virtual void poll(int timeout_ms, ChannelList* channels) = 0;

  // 在poller中新增，删除，修改channel的关注事件
  virtual void update_channel(Channel* channel) = 0;

  // 在poller中移除channel
  virtual void remove_channel(Channel* channel) = 0;

  void assertInLoopThread() const {
    // ownerLoop_->assertInLoopThread();
  }
};

}  // namespace libak
#endif
