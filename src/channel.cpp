#include "channel.h"

#include <string.h>
#include <sys/socket.h>

#include <iostream>

namespace libak {

void Channel::enable_reading() {
  events_ |= kReadEvent;
  update_channel_event_to_loop();
}

void Channel::disable_reading() {
  events_ &= ~kReadEvent;
  update_channel_event_to_loop();
}

void Channel::enable_writing() {
  events_ |= kWriteEvent;
  update_channel_event_to_loop();
}
void Channel::disable_writing() {
  events_ &= ~kWriteEvent;
  update_channel_event_to_loop();
}
void Channel::disable_all() {
  events_ = kNoneEvent;
  update_channel_event_to_loop();
}

bool Channel::is_writing() const { return events_ & kWriteEvent; }
bool Channel::is_reading() const { return events_ & kReadEvent; }
bool Channel::is_disable_all() const { return events_ == kNoneEvent; } 

void Channel::update_channel_event_to_loop() {
  loop_->update_channel(this);
}
}  // namespace libak
