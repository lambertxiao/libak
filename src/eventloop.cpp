#include <assert.h>
#include <thread>
#include <fmtlog/fmtlog.h>

#include "eventloop.h"
#include "poller.h"

namespace libak {

void EventLoop::assert_in_loop_thread() {
  assert(in_loop_thread());
};

void EventLoop::start_loop() {
  logi("Eventloop starting loop, poll_timeout_:{}", poll_timeout_);

  assert(!looping_);
  assert_in_loop_thread();
  looping_ = true;
  quit_ = false;

  while (!quit_) {
    active_channels_.clear();
    poller_->poll(poll_timeout_, &active_channels_);

    for (Channel* c : active_channels_) {
      logi("channel {} handle event", c->fd());
      c->handle_event();
    }
  }

  logi("Eventloop stop looping");
  looping_ = false;
};

void EventLoop::update_channel(Channel* c) {
  assert(c->owner_loop() == this);
  assert_in_loop_thread();
  poller_->update_channel(c);
}

bool EventLoop::in_loop_thread() {
  auto curr_thread_id = std::this_thread::get_id();
  return curr_thread_id == thread_id_;
}

void EventLoop::run_in_loop(Functor f) {
  if (in_loop_thread()) {
    f();
    return;
  }

  add_to_pending_cbs(f);
}

void EventLoop::add_to_pending_cbs(Functor f) {
  std::lock_guard lock(lock_);
  // 这里为什么要用std::move
  pending_cbs_.push_back(std::move(f));
}

}  // namespace libak
