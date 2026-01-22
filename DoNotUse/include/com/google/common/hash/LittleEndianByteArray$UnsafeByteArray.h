#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/hash/LittleEndianByteArray/LittleEndianBytes.h"
#include "com/google/common/hash/LittleEndianByteArray/UnsafeByteArray/3.h"
#include "java/security/AccessController.h"
#include "java/security/PrivilegedActionException.h"
#include "sun/misc/Unsafe.h"

namespace com {
namespace google {
namespace common {
namespace hash {


enum class LittleEndianByteArray {
   UNSAFE_LITTLE_ENDIAN,
   UNSAFE_BIG_ENDIAN;

    static const Unsafe theUnsafe = getUnsafe();
    static const int BYTE_ARRAY_BASE_OFFSET = theUnsafe.arrayBaseOffset(byte[].class);

   private LittleEndianByteArray$UnsafeByteArray() {
   }

    static Unsafe getUnsafe() {
      try {
         return Unsafe.getUnsafe();
      } catch (SecurityException var2) {
         try {
            return AccessController.doPrivileged(std::make_unique<3>());
         } catch (PrivilegedActionException var1) {
            throw RuntimeException("Could not initialize intrinsics", var1.getCause());
         }
      }
   }

   static {
      if (theUnsafe.arrayIndexScale(byte[].class) != 1) {
         throw std::make_unique<AssertionError>();
      }
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
