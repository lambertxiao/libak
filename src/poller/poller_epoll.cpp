#include <fmtlog/fmtlog.h>
#include <string.h>
#include <sys/epoll.h>
#include <unistd.h>

#include "poller.h"
#include "poller/poller_epoll.h"
#include "channel.h"

namespace libak {

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

  if (status == Channel::CH_STATUS_NEW || status == Channel::CH_STATUS_DELETED) {
    c->set_status_in_loop(Channel::CH_STATUS_ADDED);
    update(EPOLL_CTL_ADD, c);
  } else {
    if (c->is_disable_all()) {
      update(EPOLL_CTL_DEL, c);
      c->set_status_in_loop(Channel::CH_STATUS_DELETED);
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

void EpollPoller::remove_channel(Channel* c) {
  int status = c->status_in_loop();
  
  if (status == Channel::CH_STATUS_ADDED) {
    update(EPOLL_CTL_DEL, c);
  };

  c->set_status_in_loop(Channel::CH_STATUS_NEW);
}

void EpollPoller::activate_channels(int event_cnt, ChannelList* active_chs) {
  for (int i = 0; i < event_cnt; i++) {
    Channel* c = static_cast<Channel*>(events_[i].data.ptr);
    // 告诉channel发生绳么事了
    c->set_what_happen(events_[i].events);
    active_chs->push_back(c);
  }
}
  
}  // namespace libak
