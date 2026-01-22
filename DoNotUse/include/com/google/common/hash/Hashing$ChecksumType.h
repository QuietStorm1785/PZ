#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Supplier.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace hash {


enum class Hashing {
   CRC_32("CRC_32", 0, 32),
   ADLER_32("ADLER_32", 1, 32);

    const int bits;

   private Hashing$ChecksumType(int bits) {
      this.bits = bits;
   }

   public abstract Checksum get();
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
