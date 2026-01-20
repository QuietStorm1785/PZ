#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/primitives/Longs.h"

namespace com {
namespace google {
namespace common {
namespace hash {


enum class LittleEndianByteArray {
    long getLongLittleEndian(byte[] source, int offset) {
      return Longs.fromBytes(
         source[offset + 7],
         source[offset + 6],
         source[offset + 5],
         source[offset + 4],
         source[offset + 3],
         source[offset + 2],
         source[offset + 1],
         source[offset]
      );
   }

    void putLongLittleEndian(byte[] sink, int offset, long value) {
    long mask = 255L;

      for (int i = 0; i < 8; i++) {
         sink[offset + i] = (byte)((value & mask) >> i * 8);
         mask <<= 8;
      }
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
