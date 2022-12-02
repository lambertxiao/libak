#ifndef LIBAK_BUFFER_H_
#define LIBAK_BUFFER_H_

#include <assert.h>
#include <string.h>
#include <vector>
#include <algorithm>

#include "common/endian.h"

namespace libak {

// expired by muduo
// [保留区, 已读区域, 可读区, 可写区]
class Buffer {
 private:
  std::vector<char> buffer_;
  // 注意这里记录的是下标而不是实际的地址
  size_t reader_idx_;
  size_t writer_idx_;

 public:
  // 保留区的大小
  static const size_t reserve_len = 8;
  static const size_t default_buf_size = 1024;

  size_t readable_bytes() const { return writer_idx_ - reader_idx_; }

  size_t writable_bytes() const { return buffer_.size() - writer_idx_; }

  // 已经被读取走的空间里的内容是可覆盖掉的
  size_t available_bytes() const { return reader_idx_; }

  // write buffer
  void append(const char* data, size_t len) {
    ensure_writable_bytes(len);
    std::copy(data, data + len, buffer_writer_idx_addr());
    incr_writer_idx(len);
  }

  void incr_writer_idx(size_t len) {
    writer_idx_ += len;
  }

  void incr_reader_idx(size_t len) {
    assert(len <= readable_bytes());
    if (len < readable_bytes()) {
      reader_idx_ += len;
    }
    else {
      // 全部读完里，reader_idx和write_idx可以全部归零
      retrieve_idx();
    }
  }

  void retrieve_idx() {
    reader_idx_ = reserve_len;
    writer_idx_ = reserve_len;
  }

  void ensure_writable_bytes(size_t len) {
    if (writable_bytes() < len) {
      adjust_buffer(len);
    }
    assert(writable_bytes() >= len);
  }

  void adjust_buffer(size_t len) {
    // 如果内部空间不够，需要调整buffer的大小
    if (writable_bytes() + available_bytes() < len + reserve_len) {
      buffer_.resize(writer_idx_ + len);
    } else {
      // 如果内部空间够，则内部挪一挪位置
      assert(reserve_len < reader_idx_);
      size_t readable = readable_bytes();
      std::copy(
        buffer_reader_idx_addr(), 
        buffer_writer_idx_addr(), 
        buffer_begin_addr() + reserve_len);
      reader_idx_ = reserve_len;
      writer_idx_ = reader_idx_ + readable;
      assert(readable == readable_bytes());
    }
  }

  // buffer的起始地址
  const char* buffer_begin_addr() const { 
    return &*buffer_.begin();
  }

  // buffer writer_idx所在地址
  const char* buffer_writer_idx_addr() { 
    return buffer_begin_addr() + writer_idx_;
  }

  // buffer reader_idx所在地址
  const char* buffer_reader_idx_addr() {
    return buffer_begin_addr() + reader_idx_;
  }

  const char* buffer_reader_idx_addr() const {
    return buffer_begin_addr() + reader_idx_;
  }

  int64_t read_int64() {
    int64_t result = peek_int64();
    incr_reader_idx(sizeof(int64_t));
    return result;
  }

  int64_t peek_int64() const {
    assert(readable_bytes() >= sizeof(int64_t));
    int64_t be64 = 0;
    ::memcpy(&be64, buffer_reader_idx_addr(), sizeof be64);
    return common::networkToHost64(be64);
  }
};

}  // namespace libak
#endif
