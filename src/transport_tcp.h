#ifndef LIBAK_TANSPORT_TCP_H_
#define LIBAK_TANSPORT_TCP_H_

#include "libak.h"

namespace libak {

class TCPTransport : public libak::Transport {
 public:
  void encode_packet() override;
  void decode_packet() override;
};
}  // namespace libak

#endif
