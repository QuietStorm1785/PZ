#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/hash/LittleEndianByteArray/JavaLittleEndianBytes.h"
#include "com/google/common/hash/LittleEndianByteArray/LittleEndianBytes.h"
#include "com/google/common/hash/LittleEndianByteArray/UnsafeByteArray.h"
#include <filesystem>

namespace com {
namespace google {
namespace common {
namespace hash {


class LittleEndianByteArray {
public:
    static const LittleEndianBytes byteArray;

    static long load64(byte[] input, int offset) {
      assert input.length >= offset + 8;

      return byteArray.getLongLittleEndian(input, offset);
   }

    static long load64Safely(byte[] input, int offset, int length) {
    long result = 0L;
    int limit = Math.min(length, 8);

      for (int i = 0; i < limit; i++) {
         result |= (input[offset + i] & 255L) << i * 8;
      }

    return result;
   }

    static void store64(byte[] sink, int offset, long value) {
      assert offset >= 0 && offset + 8 <= sink.length;

      byteArray.putLongLittleEndian(sink, offset, value);
   }

    static int load32(byte[] source, int offset) {
      return source[offset] & 0xFF | (source[offset + 1] & 0xFF) << 8 | (source[offset + 2] & 0xFF) << 16 | (source[offset + 3] & 0xFF) << 24;
   }

    static bool usingUnsafe() {
      return dynamic_cast<UnsafeByteArray*>(byteArray) != nullptr;
   }

    private LittleEndianByteArray() {
   }

   static {
    LittleEndianBytes theGetter = JavaLittleEndianBytes.INSTANCE;

      try {
    std::string arch = System.getProperty("os.arch");
         if ("amd64" == arch) || "aarch64" == arch)) {
            theGetter = ByteOrder.nativeOrder() == ByteOrder.LITTLE_ENDIAN) ? UnsafeByteArray.UNSAFE_LITTLE_ENDIAN : UnsafeByteArray.UNSAFE_BIG_ENDIAN;
         }
      } catch (Throwable var2) {
      }

      byteArray = theGetter;
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
