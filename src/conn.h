#include <stdint.h>

namespace libak {

// 链接是一个逻辑上的通道，可读可写
class Connection {
 public:
  void read(char* data, uint32_t len);
  void write(char* data, uint32_t len);
};

}  // namespace libak
