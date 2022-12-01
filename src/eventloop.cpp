#include "eventloop.h"

#include <assert.h>

#include <thread>

#include "fmtlog/fmtlog.h"
#include "poller.h"

namespace libak {

EventLoop::EventLoop()
    : looping_(false), quit_(false), thread_id_(std::this_thread::get_id()), poller_(Poller::create_default_poller()) {
  logi("eventloop create in {} thread", thread_id_);
};

void EventLoop::assert_in_loop_thread() {
  auto curr_thread_id = std::this_thread::get_id();
  assert(curr_thread_id == thread_id_);
};

void EventLoop::start_loop() {
  assert(!looping_);
  assert_in_loop_thread();
  looping_ = true;
  quit_ = false;

  logi("Eventloop {} starting loop", this);

  while (!quit_) {
    active_channels_.clear();
    poller_->poll(poll_timeout_, &active_channels_);

    for (Channel* channel : active_channels_) {
      channel->handle_event();
    }
  }

  logi("Eventloop {} stop looping", this);
  looping_ = false;
};

void EventLoop::update_channel(Channel* c) {
  assert(c->owner_loop() == this);
  assert_in_loop_thread();
  poller_->update_channel(c);
}

}  // namespace libak
