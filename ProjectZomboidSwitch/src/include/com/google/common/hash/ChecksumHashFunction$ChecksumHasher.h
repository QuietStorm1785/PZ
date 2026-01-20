#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace hash {


class ChecksumHashFunction {
public:
    const Checksum checksum;

   private ChecksumHashFunction$ChecksumHasher(ChecksumHashFunction var1, Checksum checksum) {
      this.this$0 = var1;
      this.checksum = (Checksum)Preconditions.checkNotNull(checksum);
   }

    void update(uint8_t b) {
      this.checksum.update(b);
   }

    void update(byte[] bytes, int off, int len) {
      this.checksum.update(bytes, off, len);
   }

    HashCode hash() {
    long value = this.checksum.getValue();
      return ChecksumHashFunction.access$100(this.this$0) == 32 ? HashCode.fromInt((int)value) : HashCode.fromLong(value);
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
