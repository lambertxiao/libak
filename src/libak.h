#ifndef LAMBERTX_LIBAK_H_
#define LAMBERTX_LIBAK_H_

#include <string>
#include "proto.h"

namespace libak {

class ProtoCenter {
 public:
  static void regist_proto(Proto& proto) { 
    return; 
  }
  ;
  static Proto* get_proto(std::string prokey) { 
    return NULL;
  };
};

class Callback {};

}  // namespace libak
#endif
