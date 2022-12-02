#include "proto_center.h"

namespace libak {

void ProtoCenter::regist_proto(Proto* proto) {
  protos[proto->key_] = proto;
};

Proto* ProtoCenter::get_proto(std::string prokey) { 
  if (protos.count(prokey) > 0) {
    return protos[prokey];
  }

  return NULL;
};
}
