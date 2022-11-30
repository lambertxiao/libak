#ifndef LIBAK_POLLER_EPOLL_H_
#define LIBAK_POLLER_EPOLL_H_

#include "poller.h"

namespace libak {
namespace poller {

class EpollPoller : public Poller {

 private:
  using EventList = std::vector<struct epoll_event>;
  EventList events_;

  int epollfd_;

  static const int init_event_list_size = 32;

  // 将发生事件的事件标记到channel上
  void activate_channels(int event_cnt, ChannelList* cl);

 public:
  void poll(int timeout_ms, ChannelList* channels) override;
  void update_channel(Channel* channel) override;
  void remove_channel(Channel* channel) override;
};

}  // namespace poller
}  // namespace libak
#endif
