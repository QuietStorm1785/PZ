#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/annotations/VisibleForTesting.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/primitives/UnsignedBytes/LexicographicalComparatorHolder.h"
#include "com/google/common/primitives/UnsignedBytes/LexicographicalComparatorHolder/PureJavaComparator.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace primitives {


class UnsignedBytes {
public:
    static const uint8_t MAX_POWER_OF_TWO = -128;
    static const uint8_t MAX_VALUE = -1;
    static const int UNSIGNED_MASK = 255;

    private UnsignedBytes() {
   }

    static int toInt(uint8_t value) {
      return value & 0xFF;
   }

    static uint8_t checkedCast(long value) {
      if (value >> 8 != 0L) {
         throw IllegalArgumentException("Out of range: " + value);
      } else {
         return (byte)value;
      }
   }

    static uint8_t saturatedCast(long value) {
      if (value > toInt((byte)-1)) {
         return -1;
      } else {
         return value < 0L ? 0 : (byte)value;
      }
   }

    static int compare(uint8_t a, uint8_t b) {
    return toInt();
   }

    static uint8_t min(byte... array) {
      Preconditions.checkArgument(array.length > 0);
    int min = toInt(array[0]);

      for (int i = 1; i < array.length; i++) {
    int next = toInt(array[i]);
         if (next < min) {
            min = next;
         }
      }

      return (byte)min;
   }

    static uint8_t max(byte... array) {
      Preconditions.checkArgument(array.length > 0);
    int max = toInt(array[0]);

      for (int i = 1; i < array.length; i++) {
    int next = toInt(array[i]);
         if (next > max) {
            max = next;
         }
      }

      return (byte)max;
   }

    static std::string toString(uint8_t x) {
    return toString();
   }

    static std::string toString(uint8_t x, int radix) {
      Preconditions.checkArgument(radix >= 2 && radix <= 36, "radix (%s) must be between char.MIN_RADIX and char.MAX_RADIX", radix);
      return int.toString(toInt(x), radix);
   }

    static uint8_t parseUnsignedByte(const std::string& string) {
    return parseUnsignedByte();
   }

    static uint8_t parseUnsignedByte(const std::string& string, int radix) {
    int parse = int.parseInt((std::string)Preconditions.checkNotNull(string), radix);
      if (parse >> 8 == 0) {
         return (byte)parse;
      } else {
         throw NumberFormatException("out of range: " + parse);
      }
   }

    static std::string join(const std::string& separator, byte... array) {
      Preconditions.checkNotNull(separator);
      if (array.length == 0) {
         return "";
      } else {
    std::stringstream builder = new std::stringstream(array.length * (3 + separator.length()));
         builder.append(toInt(array[0]));

         for (int i = 1; i < array.length; i++) {
            builder.append(separator).append(toString(array[i]));
         }

         return builder;
      }
   }

   public static Comparator<byte[]> lexicographicalComparator() {
      return LexicographicalComparatorHolder.BEST_COMPARATOR;
   }

   static Comparator<byte[]> lexicographicalComparatorJavaImpl() {
      return PureJavaComparator.INSTANCE;
   }
}
} // namespace primitives
} // namespace common
} // namespace google
} // namespace com
