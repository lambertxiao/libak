#ifndef LIBAK_CONN_H_
#define LIBAK_CONN_H_

#include <poll.h>
#include <stdint.h>

#include "poller.h"
#include "eventloop.h"
#include "msg_en_decoder.h"

namespace libak {

// Channel是一个逻辑上的通道，可读可写
class Channel {
 public:
  const static int kNoneEvent = 0;
  const static int kReadEvent = POLLIN | POLLPRI;
  const static int kWriteEvent = POLLOUT;

  Channel(EventLoop* loop, int fd) : 
  loop_(loop), fd_(fd), status_in_loop_(Poller::CH_STATUS_NEW) {}

  void write(void* data, int data_len);
  void handle_event();
  void set_receive_events(int revt) { revents_ = revt; }  // used by pollers

  const int fd() const { return fd_; }
  const uint32_t events() const { return events_; }

  // 控制channel的读写状态
  void enable_reading();
  void disable_reading();
  void enable_writing();
  void disable_writing();
  void disable_all();

  // 通知eventloop说channel的关注事件更新了
  void update_channel_event_to_loop();

  // 获取channel的读写状态
  bool is_writing() const;
  bool is_reading() const;
  bool is_disable_all() const;

  // 交由poller设置
  void set_status_in_loop(Poller::CHStatus status) {
    status_in_loop_ = status;
  } 

  Poller::CHStatus status_in_loop() {
    return status_in_loop_;
  }

  EventLoop* owner_loop() {
    return loop_;
  }

 private:
  int fd_;

  // 记录channel收到的事件
  int revents_;

  // 记录channel当前所关注的事件
  uint32_t events_;

  // 记录channel的eventloop中的状态
  Poller::CHStatus status_in_loop_;

  // 一个channel会由一个eventloop来控制
  // channel通过告诉loop它所关心的事件，然后等着loop来调用handle_event即可
  EventLoop* loop_;
};

}  // namespace libak
#endif
