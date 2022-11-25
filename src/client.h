#ifndef LIBAK_CLIENT_H_
#define LIBAK_CLIENT_H_

#include "libak.h"
#include "transport.h"
#include "transport_pool.h"

namespace libak {

class Client {
 public:
  template <typename Msg>
  void send(Endpoint ep, std::string rt_key, Msg msg);

  void async_send(Endpoint ep, std::string rt_key, void* msg, uint32_t len, Callback cb);
  void regist_rt(std::string key, RoundTripper rt);

 private:
  TransportPool* transport_pool;
};

}  // namespace libak

#endif
