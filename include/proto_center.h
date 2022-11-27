#ifndef LIBAK_PROTO_CENTER_H_
#define LIBAK_PROTO_CENTER_H_

#include <unordered_map>
#include "proto.h"

namespace libak {
class ProtoCenter {
 public:
  static void regist_proto(Proto* proto);
  static Proto* get_proto(std::string prokey);
  inline static std::unordered_map<std::string, Proto*> protos;
 private:
};
}
#endif
