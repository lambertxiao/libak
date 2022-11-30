#include "poller/poller_epoll.h"

#include <sys/epoll.h>
#include <assert.h>
#include <unistd.h>
#include <fmtlog/fmtlog.h>
#include <string.h>

namespace libak {
namespace poller {

EpollPoller::EpollPoller() : 
epollfd_(epoll_create1(EPOLL_CLOEXEC)),
events_(init_event_list_size)
{
  assert(epollfd_ > 0);
};

EpollPoller::~EpollPoller()
{
  ::close(epollfd_);
}

void EpollPoller::poll(int timeout_ms, ChannelList* channels){
  logd("poll channel cnt is {}", channels->size());

  int event_cnt = epoll_wait(
    epollfd_, &*events_.begin(),
    static_cast<int>(events_.size()),
    timeout_ms
  );

  if (event_cnt == 0) {
    logd("no events happened", event_cnt);
    return;
  }

  if (event_cnt < 0) {
    logd("epoll_wait error, event_cnt:{}", event_cnt);
    return;
  }

  logd("{} events happened", event_cnt);
  activate_channels(event_cnt, channels);
};
}  // namespace poller
}  // namespace libak
