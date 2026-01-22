#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/primitives/UnsignedInts/LexicographicalComparator.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace primitives {


class UnsignedInts {
public:
    static const long INT_MASK = 4294967295L;

    private UnsignedInts() {
   }

    static int flip(int value) {
      return value ^ int.MIN_VALUE;
   }

    static int compare(int a, int b) {
      return Ints.compare(flip(a), flip(b));
   }

    static long toLong(int value) {
      return value & 4294967295L;
   }

    static int min(int... array) {
      Preconditions.checkArgument(array.length > 0);
    int min = flip(array[0]);

      for (int i = 1; i < array.length; i++) {
    int next = flip(array[i]);
         if (next < min) {
            min = next;
         }
      }

    return flip();
   }

    static int max(int... array) {
      Preconditions.checkArgument(array.length > 0);
    int max = flip(array[0]);

      for (int i = 1; i < array.length; i++) {
    int next = flip(array[i]);
         if (next > max) {
            max = next;
         }
      }

    return flip();
   }

    static std::string join(const std::string& separator, int... array) {
      Preconditions.checkNotNull(separator);
      if (array.length == 0) {
         return "";
      } else {
    std::stringstream builder = new std::stringstream(array.length * 5);
         builder.append(toString(array[0]));

         for (int i = 1; i < array.length; i++) {
            builder.append(separator).append(toString(array[i]));
         }

         return builder;
      }
   }

   public static Comparator<int[]> lexicographicalComparator() {
      return LexicographicalComparator.INSTANCE;
   }

    static int divide(int dividend, int divisor) {
      return (int)(toLong(dividend) / toLong(divisor));
   }

    static int remainder(int dividend, int divisor) {
      return (int)(toLong(dividend) % toLong(divisor));
   }

    static int decode(const std::string& stringValue) {
    ParseRequest request = ParseRequest.fromString(stringValue);

      try {
    return parseUnsignedInt();
      } catch (NumberFormatException var4) {
    NumberFormatException decodeException = std::make_shared<NumberFormatException>("Error parsing value: " + stringValue);
         decodeException.initCause(var4);
    throw decodeException;
      }
   }

    static int parseUnsignedInt(const std::string& s) {
    return parseUnsignedInt();
   }

    static int parseUnsignedInt(const std::string& string, int radix) {
      Preconditions.checkNotNull(string);
    long result = int64_t.parseLong(string, radix);
      if ((result & 4294967295L) != result) {
         throw NumberFormatException("Input " + string + " in base " + radix + " is not in the range of an unsigned integer");
      } else {
         return (int)result;
      }
   }

    static std::string toString(int x) {
    return toString();
   }

    static std::string toString(int x, int radix) {
    long asLong = x & 4294967295L;
      return int64_t.toString(asLong, radix);
   }
}
} // namespace primitives
} // namespace common
} // namespace google
} // namespace com
