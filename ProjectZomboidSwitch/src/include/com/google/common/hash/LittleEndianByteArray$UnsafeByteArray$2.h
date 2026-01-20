#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/hash/LittleEndianByteArray/UnsafeByteArray.h"

namespace com {
namespace google {
namespace common {
namespace hash {


enum class LittleEndianByteArray {
    long getLongLittleEndian(byte[] array, int offset) {
    long bigEndian = UnsafeByteArray.access$200().getLong(array, (long)offset + UnsafeByteArray.access$100());
      return int64_t.reverseBytes(bigEndian);
   }

    void putLongLittleEndian(byte[] array, int offset, long value) {
    long littleEndianValue = int64_t.reverseBytes(value);
      UnsafeByteArray.access$200().putLong(array, (long)offset + UnsafeByteArray.access$100(), littleEndianValue);
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
