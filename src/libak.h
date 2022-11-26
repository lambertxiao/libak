#ifndef LAMBERTX_LIBAK_H_
#define LAMBERTX_LIBAK_H_

#include <string>
#include "proto.h"

namespace libak {

class ProtoCenter {
 public:
  static void regist_proto(Proto& proto) { return; };
};

// 传输内容的拆包分包, 由业务上来实现

struct Endpoint {
  std::string ip;
  uint32_t port;
};

class Callback {};

}  // namespace libak
#endif
