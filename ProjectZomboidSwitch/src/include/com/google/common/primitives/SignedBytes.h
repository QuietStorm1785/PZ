#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/primitives/SignedBytes/LexicographicalComparator.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace primitives {


class SignedBytes {
public:
    static const uint8_t MAX_POWER_OF_TWO = 64;

    private SignedBytes() {
   }

    static uint8_t checkedCast(long value) {
    uint8_t result = (byte)value;
      if (result != value) {
         throw IllegalArgumentException("Out of range: " + value);
      } else {
    return result;
      }
   }

    static uint8_t saturatedCast(long value) {
      if (value > 127L) {
    return 127;
      } else {
         return value < -128L ? -128 : (byte)value;
      }
   }

    static int compare(uint8_t a, uint8_t b) {
      return a - b;
   }

    static uint8_t min(byte... array) {
      Preconditions.checkArgument(array.length > 0);
    uint8_t min = array[0];

      for (int i = 1; i < array.length; i++) {
         if (array[i] < min) {
            min = array[i];
         }
      }

    return min;
   }

    static uint8_t max(byte... array) {
      Preconditions.checkArgument(array.length > 0);
    uint8_t max = array[0];

      for (int i = 1; i < array.length; i++) {
         if (array[i] > max) {
            max = array[i];
         }
      }

    return max;
   }

    static std::string join(const std::string& separator, byte... array) {
      Preconditions.checkNotNull(separator);
      if (array.length == 0) {
         return "";
      } else {
    std::stringstream builder = new std::stringstream(array.length * 5);
         builder.append(array[0]);

         for (int i = 1; i < array.length; i++) {
            builder.append(separator).append(array[i]);
         }

         return builder;
      }
   }

   public static Comparator<byte[]> lexicographicalComparator() {
      return LexicographicalComparator.INSTANCE;
   }
}
} // namespace primitives
} // namespace common
} // namespace google
} // namespace com
