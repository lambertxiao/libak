#include "poller/poller_epoll.h"

#include <assert.h>
#include <fmtlog/fmtlog.h>
#include <string.h>
#include <sys/epoll.h>
#include <unistd.h>

namespace libak {
namespace poller {

EpollPoller::EpollPoller() : epollfd_(epoll_create1(EPOLL_CLOEXEC)), events_(init_event_list_size) {
  assert(epollfd_ > 0);
};

EpollPoller::~EpollPoller() { ::close(epollfd_); }

void EpollPoller::poll(int timeout_ms, ChannelList* channels) {
  logd("poll channel cnt is {}", channels->size());

  int event_cnt = epoll_wait(epollfd_, &*events_.begin(), static_cast<int>(events_.size()), timeout_ms);

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

void EpollPoller::update_channel(Channel* c) {
  int status = c->status_in_loop();

  if (status == CH_STATUS_NEW || status == CH_STATUS_DELETED) {
    int fd = c->fd();
    c->set_status_in_loop(CH_STATUS_ADDED);
    update(EPOLL_CTL_ADD, c);
  } else {
    if (c->is_disable_all()) {
      update(EPOLL_CTL_DEL, c);
      c->set_status_in_loop(CH_STATUS_DELETED);
    } else {
      update(EPOLL_CTL_MOD, c);
    }
  }
};

void EpollPoller::update(int epoll_op, Channel* c) {
  auto fd = c->fd();

  epoll_event event;
  // 设置关注的事件
  event.events = c->events();
  // 将channel托管给epoll
  event.data.ptr = c;

  logd("epoll_ctl op:{} fd:{} events:{}", epoll_op, fd, c->events());
  epoll_ctl(epollfd_, epoll_op, fd, &event);
};

}  // namespace poller
}  // namespace libak
