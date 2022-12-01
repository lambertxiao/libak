#ifndef LIBAK_EVENTLOOP_H_
#define LIBAK_EVENTLOOP_H_

#include <sys/epoll.h>
#include <functional>
#include <memory>
#include <thread>

#include "common/noncopyable.h"
#include "poller.h"
#include "channel.h"

namespace libak {

class EventLoop : common::noncopyable {
 public:
  // 启动事件循环
  void start_loop();

  // 退出事件循环
  void quit_loop();

  // channel相关的方法
  void update_channel(Channel* c);
  void delete_channel(Channel* c);

 private:
  using ChannelList = std::vector<Channel*>;

  // 标记是否开启循环
  bool looping_; 
  // 标记是否需要退出
  bool quit_;
  // 执行poll的超时时间
  int poll_timeout_;
  // 所属线程
  std::thread::id thread_id_;

  std::unique_ptr<Poller> poller_;
  
  // 当前发生事件的channel
  ChannelList active_channels_;

  // eventloop只能在创建它的线程中执行
  void assert_in_loop_thread();
};
 
}  // namespace libak

#endif
