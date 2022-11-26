#ifndef LIBAK_CONN_GENERATOR_H_
#define LIBAK_CONN_GENERATOR_H_

#include "conn.h"
#include "endpoint.h"

namespace libak {
  
// 负责生成具体的连接，如tcp链接
class ConnGenerator {
 public:
  virtual Connection* gen(Endpoint ep) = 0;
};
}  // namespace libak
#endif
