#include "libak.h"
#include <iostream>

namespace libak {

void* Client::send(Endpoint ep, std::string prokey, void* msg) {
  // 3. 等待事件回调
  // 4. 处理回调消息，回消息给调用者
  auto transport = transport_pool->get_transport(ep, prokey);
  transport->send(msg);

  return NULL;
}

}  // namespace libak
