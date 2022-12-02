#include "channel.h"

#include <string.h>
#include <sys/socket.h>

#include <iostream>

#include "eventloop.h"

namespace libak {

void Channel::enable_reading() {
  events_ |= kReadEvent;
  tell_loop_ch_changed();
}

void Channel::disable_reading() {
  events_ &= ~kReadEvent;
  tell_loop_ch_changed();
}

void Channel::enable_writing() {
  events_ |= kWriteEvent;
  tell_loop_ch_changed();
}
void Channel::disable_writing() {
  events_ &= ~kWriteEvent;
  tell_loop_ch_changed();
}
void Channel::disable_all() {
  events_ = kNoneEvent;
  tell_loop_ch_changed();
}

bool Channel::is_writing() const { return events_ & kWriteEvent; }
bool Channel::is_reading() const { return events_ & kReadEvent; }
bool Channel::is_disable_all() const { return events_ == kNoneEvent; }
void Channel::tell_loop_ch_changed() { loop_->update_channel(this); }

void Channel::handle_event() {
  if ((recv_events_ & POLLHUP) && !(recv_events_ & POLLIN)) {
    logw("fd:{} POLLHUP && !POLLIN");
    if (close_cb_) close_cb_();
  }

  if (recv_events_ & POLLNVAL) {
    logw("fd:{} POLLNVAL");
  }

  if (recv_events_ & (POLLERR | POLLNVAL)) {
    logw("fd:{} POLLERR or POLLNVAL");
    if (err_cb_) err_cb_();
  }

  if (recv_events_ & (POLLIN | POLLPRI | POLLRDHUP)) {
    logd("fd:{} POLLIN or POLLPRI or POLLRDHUP");
    if (read_cb_) read_cb_();
  }

  if (recv_events_ & POLLOUT) {
    logd("fd:{} POLLOUT");
    if (write_cb_) write_cb_();
  }
};

}  // namespace libak
