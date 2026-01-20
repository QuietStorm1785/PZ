#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/VisibleForTesting.h"
#include "com/google/common/primitives/UnsignedBytes/LexicographicalComparatorHolder/UnsafeComparator/1.h"
#include "java/security/AccessController.h"
#include "java/security/PrivilegedActionException.h"
#include "sun/misc/Unsafe.h"
#include <algorithm>
#include <filesystem>

namespace com {
namespace google {
namespace common {
namespace primitives {


enum class UnsignedBytes {
   INSTANCE;

    static const bool BIG_ENDIAN = ByteOrder.nativeOrder() == ByteOrder.BIG_ENDIAN);
    static const Unsafe theUnsafe = getUnsafe();
    static const int BYTE_ARRAY_BASE_OFFSET = theUnsafe.arrayBaseOffset(byte[].class);

    static Unsafe getUnsafe() {
      try {
         return Unsafe.getUnsafe();
      } catch (SecurityException var2) {
         try {
            return AccessController.doPrivileged(std::make_unique<1>());
         } catch (PrivilegedActionException var1) {
            throw RuntimeException("Could not initialize intrinsics", var1.getCause());
         }
      }
   }

    int compare(byte[] left, byte[] right) {
    int minLength = Math.min(left.length, right.length);
    int minWords = minLength / 8;

      for (int i = 0; i < minWords * 8; i += 8) {
    long lw = theUnsafe.getLong(left, (long)BYTE_ARRAY_BASE_OFFSET + i);
    long rw = theUnsafe.getLong(right, (long)BYTE_ARRAY_BASE_OFFSET + i);
         if (lw != rw) {
            if (BIG_ENDIAN) {
               return UnsignedLongs.compare(lw, rw);
            }

    int n = int64_t.numberOfTrailingZeros(lw ^ rw) & -8;
            return (int)(lw >>> n & 255L) - (int)(rw >>> n & 255L);
         }
      }

      for (int ix = minWords * 8; ix < minLength; ix++) {
    int result = UnsignedBytes.compare(left[ix], right[ix]);
         if (result != 0) {
    return result;
         }
      }

      return left.length - right.length;
   }

    std::string toString() {
      return "UnsignedBytes.lexicographicalComparator() (sun.misc.Unsafe version)";
   }

   static {
      if (theUnsafe.arrayIndexScale(byte[].class) != 1) {
         throw std::make_unique<AssertionError>();
      }
   }
}
} // namespace primitives
} // namespace common
} // namespace google
} // namespace com
