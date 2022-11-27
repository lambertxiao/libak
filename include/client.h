#ifndef LIBAK_CLIENT_H_
#define LIBAK_CLIENT_H_

#include "transport.h"
#include "transport_pool.h"

namespace libak {

class Client {
 public:
  template <typename Msg>
  void* send(Endpoint ep, std::string prokey, Msg& msg) {
    // 3. 等待事件回调
    // 4. 处理回调消息，回消息给调用者
    auto transport = transport_pool->get_transport(ep, prokey);
    transport->send(msg);

    return NULL;
  }

  // template <typename Msg>
  // void async_send(Endpoint ep, std::string rt_key, Msg msg, Callback cb);

 private:
  TransportPool* transport_pool;
};

}  // namespace libak

#endif
