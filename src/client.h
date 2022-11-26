#ifndef LIBAK_CLIENT_H_
#define LIBAK_CLIENT_H_

#include "libak.h"
#include "transport.h"
#include "transport_pool.h"

namespace libak {

class Client {
 public:
  template <typename Msg>
  void* send(Endpoint ep, std::string rt_key, Msg msg);

  template <typename Msg>
  void async_send(Endpoint ep, std::string rt_key, Msg msg, Callback cb);

 private:
  TransportPool* transport_pool;
};

}  // namespace libak

#endif
