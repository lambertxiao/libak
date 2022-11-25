#include <stdint.h>

namespace libak {

class Connection {
 public:
  void read(char* data, uint32_t len);
  void write(char* data, uint32_t len);
};

class ConnGenerator {
 public:
  Connection* gen();
};

}  // namespace libak
