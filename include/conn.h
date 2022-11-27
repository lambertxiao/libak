#ifndef LIBAK_CONN_H_
#define LIBAK_CONN_H_

#include <stdint.h>
#include "msg_en_decoder.h"

namespace libak {

// 链接是一个逻辑上的通道，可读可写
class Connection {
 public:
  // void read(char* data, uint32_t len);
  void write(EncMsg& msg);
};

}  // namespace libak
#endif
