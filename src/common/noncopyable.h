#ifndef LIBAK_COMMON_NOCOPYABLE_H_
#define LIBAK_COMMON_NOCOPYABLE_H_

namespace libak {
namespace common {

class noncopyable {
 public:
  noncopyable(const noncopyable&) = delete;
  void operator=(const noncopyable&) = delete;

 protected:
  noncopyable() = default;
  ~noncopyable() = default;
};

}  // namespace base
}  // namespace libak

#endif
