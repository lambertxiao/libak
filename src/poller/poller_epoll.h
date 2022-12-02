#ifndef LIBAK_POLLER_EPOLL_H_
#define LIBAK_POLLER_EPOLL_H_

#include <sys/epoll.h>
#include <assert.h>
#include <unistd.h>

#include "poller.h"
#include "channel.h"

namespace libak {

class Poller;

class EpollPoller : public Poller {
 private:
  int epollfd_;
  
  using EventList = std::vector<struct epoll_event>;
  // 将该事件集合交由epoll_wait来填充发生的事件
  EventList events_;

  // 初始事件集大小
  static const int init_event_list_size = 32;

  // 将发生事件的事件标记到channel上
  void activate_channels(int event_cnt, ChannelList* cl);

 public:
  EpollPoller() : epollfd_(epoll_create1(EPOLL_CLOEXEC)), events_(init_event_list_size) {
    assert(epollfd_ > 0);
  };

  ~EpollPoller() { ::close(epollfd_); }

  static Poller* create() {
    return new EpollPoller();
  }

  void poll(int timeout_ms, ChannelList* channels) override;
  void update_channel(Channel* channel) override;
  void remove_channel(Channel* channel) override;

  void update(int epoll_op, Channel* c);

  const char* operationToString(int op) {
    switch (op) {
      case EPOLL_CTL_ADD:
        return "ADD";
      case EPOLL_CTL_DEL:
        return "DEL";
      case EPOLL_CTL_MOD:
        return "MOD";
      default:
        return "Unknown Operation";
    }
  }
};

}  // namespace libak
#endif
