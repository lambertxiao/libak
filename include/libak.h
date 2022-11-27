#ifndef LAMBERTX_LIBAK_H_
#define LAMBERTX_LIBAK_H_

#include <string>
#include "proto.h"
#include "client.h"
#include "conn_generator.h"
#include "conn_generator_tcp.h"
#include "conn.h"
#include "endpoint.h"
#include "msg_en_decoder.h"
#include "proto.h"
#include "transport_pool.h"
#include "transport.h"

namespace libak {

class ProtoCenter {
 public:
  static void regist_proto(Proto& proto) { 
    return; 
  };
  
  static Proto* get_proto(std::string prokey) { 
    return NULL;
  };
};

class Callback {};

}  // namespace libak
#endif
