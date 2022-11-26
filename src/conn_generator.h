#include "conn.h"
#include "endpoint.h"

namespace libak {
class ConnGenerator {
 public:
  Connection* gen(Endpoint ep);
};
}  // namespace libak
