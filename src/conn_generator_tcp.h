#include "conn.h"
#include "conn_generator.h"

namespace libak {
class TCPConnGenerator : public ConnGenerator {
 public:
  Connection* gen();
};
}  // namespace libak
