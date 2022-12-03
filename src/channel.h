#ifndef LIBAK_CHANNEL_H_
#define LIBAK_CHANNEL_H_

#include <poll.h>
#include <stdint.h>
#include <functional>

namespace libak {

class EventLoop;
class Poller;

// Channel是一个逻辑上的通道，可读可写
class Channel {
 public:
  const static int kNoneEvent = 0;
  const static int kReadEvent = POLLIN | POLLPRI;
  const static int kWriteEvent = POLLOUT;

  // Channel的事件回调
  using CHEventCB = std::function<void()>;

  // channel在poller中的状态
  enum CHStatus {
    CH_STATUS_NEW, // 未添加
    CH_STATUS_ADDED, // 已添加
    CH_STATUS_DELETED // 已删除
  };

  Channel(EventLoop* loop, int fd) : 
  loop_(loop), fd_(fd), status_in_loop_(CH_STATUS_NEW) {}

  void write(void* data, int data_len);
  void handle_event();
  void set_what_happen(int revt) { recv_events_ = revt; }  // used by pollers

  const int fd() const { return fd_; }
  const uint32_t events() const { return events_; }

  // 控制channel的读写状态
  void watch_read();
  void unwatch_read();
  void watch_write();
  void unwatch_write();
  void disable_all();

  // 通知eventloop说channel的关注事件更新了
  void tell_loop_ch_changed();

  // 获取channel的读写状态
  bool is_writing() const;
  bool is_reading() const;
  bool is_disable_all() const;

  // 交由poller设置
  void set_status_in_loop(CHStatus status) {
    status_in_loop_ = status;
  } 

  CHStatus status_in_loop() {
    return status_in_loop_;
  }

  EventLoop* owner_loop() {
    return loop_;
  }

  // 设置channel的事件回调
  void set_read_cb(CHEventCB cb) { read_cb_ = cb; }
  void set_write_cb(CHEventCB cb) { write_cb_ = cb; }
  void set_close_cb(CHEventCB cb) { close_cb_ = cb; }
  void set_err_cb(CHEventCB cb) { err_cb_ = cb; }

 private:
  // 一个channel会由一个eventloop来控制
  // channel通过告诉loop它所关心的事件，然后等着loop来调用handle_event即可
  EventLoop* loop_;

  int fd_;

  // 记录channel的eventloop中的状态
  CHStatus status_in_loop_;

  // 由poller设置channel当前发生的事件
  int recv_events_;

  // 记录channel当前所关注的事件
  uint32_t events_;

  // channel的回调
  CHEventCB read_cb_;
  CHEventCB write_cb_;
  CHEventCB err_cb_;
  CHEventCB close_cb_;
};

}  // namespace libak
#endif
