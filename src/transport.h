#ifndef LIBAK_TANSPORT_H_
#define LIBAK_TANSPORT_H_

#include "libak.h"

namespace libak {

class Transport {
 public:
  virtual bool is_alive() = 0;
  virtual void encode_packet() = 0;
  virtual void decode_packet() = 0;
};
}  // namespace libak

#endif
