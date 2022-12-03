#ifndef LIBAK_LOG_H_
#define LIBAK_LOG_H_

#include <fmtlog/fmtlog.h>

namespace libak {
  
void set_log_level() {
  fmtlog::setLogLevel(fmtlog::DBG);
  fmtlog::startPollingThread(1);
}
}  // namespace libak

#endif
