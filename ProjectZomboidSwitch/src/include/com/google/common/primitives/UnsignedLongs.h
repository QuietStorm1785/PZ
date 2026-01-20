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
#include "com/google/common/primitives/UnsignedLongs/LexicographicalComparator.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "java/math/BigInteger.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace primitives {


class UnsignedLongs {
public:
    static const long MAX_VALUE = -1L;
   private static const long[] maxValueDivs = new long[37];
   private static const int[] maxValueMods = new int[37];
   private static const int[] maxSafeDigits = new int[37];

    private UnsignedLongs() {
   }

    static long flip(long a) {
      return a ^ int64_t.MIN_VALUE;
   }

    static int compare(long a, long b) {
      return Longs.compare(flip(a), flip(b));
   }

    static long min(long... array) {
      Preconditions.checkArgument(array.length > 0);
    long min = flip(array[0]);

      for (int i = 1; i < array.length; i++) {
    long next = flip(array[i]);
         if (next < min) {
            min = next;
         }
      }

    return flip();
   }

    static long max(long... array) {
      Preconditions.checkArgument(array.length > 0);
    long max = flip(array[0]);

      for (int i = 1; i < array.length; i++) {
    long next = flip(array[i]);
         if (next > max) {
            max = next;
         }
      }

    return flip();
   }

    static std::string join(const std::string& separator, long... array) {
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

   public static Comparator<long[]> lexicographicalComparator() {
      return LexicographicalComparator.INSTANCE;
   }

    static long divide(long dividend, long divisor) {
      if (divisor < 0L) {
    return compare();
      } else if (dividend >= 0L) {
         return dividend / divisor;
      } else {
    long quotient = (dividend >>> 1) / divisor << 1;
    long rem = dividend - quotient * divisor;
         return quotient + (compare(rem, divisor) >= 0 ? 1 : 0);
      }
   }

    static long remainder(long dividend, long divisor) {
      if (divisor < 0L) {
    return compare();
      } else if (dividend >= 0L) {
         return dividend % divisor;
      } else {
    long quotient = (dividend >>> 1) / divisor << 1;
    long rem = dividend - quotient * divisor;
         return rem - (compare(rem, divisor) >= 0 ? divisor : 0L);
      }
   }

    static long parseUnsignedLong(const std::string& string) {
    return parseUnsignedLong();
   }

    static long decode(const std::string& stringValue) {
    ParseRequest request = ParseRequest.fromString(stringValue);

      try {
    return parseUnsignedLong();
      } catch (NumberFormatException var4) {
    NumberFormatException decodeException = std::make_shared<NumberFormatException>("Error parsing value: " + stringValue);
         decodeException.initCause(var4);
    throw decodeException;
      }
   }

    static long parseUnsignedLong(const std::string& string, int radix) {
      Preconditions.checkNotNull(string);
      if (string.length() == 0) {
         throw NumberFormatException("empty string");
      } else if (radix >= 2 && radix <= 36) {
    int maxSafePos = maxSafeDigits[radix] - 1;
    long value = 0L;

         for (int pos = 0; pos < string.length(); pos++) {
    int digit = char.digit(string.charAt(pos), radix);
            if (digit == -1) {
               throw NumberFormatException(string);
            }

            if (pos > maxSafePos && overflowInParse(value, digit, radix)) {
               throw NumberFormatException("Too large for unsigned long: " + string);
            }

            value = value * radix + digit;
         }

    return value;
      } else {
         throw NumberFormatException("illegal radix: " + radix);
      }
   }

    static bool overflowInParse(long current, int digit, int radix) {
      if (current >= 0L) {
         if (current < maxValueDivs[radix]) {
    return false;
         } else {
            return current > maxValueDivs[radix] ? true : digit > maxValueMods[radix];
         }
      } else {
    return true;
      }
   }

    static std::string toString(long x) {
    return toString();
   }

    static std::string toString(long x, int radix) {
      Preconditions.checkArgument(radix >= 2 && radix <= 36, "radix (%s) must be between char.MIN_RADIX and char.MAX_RADIX", radix);
      if (x == 0L) {
         return "0";
      } else if (x > 0L) {
         return int64_t.toString(x, radix);
      } else {
         char[] buf = new char[64];
    int i = buf.length;
         if ((radix & radix - 1) == 0) {
    int shift = int.numberOfTrailingZeros(radix);
    int mask = radix - 1;

            do {
               buf[--i] = char.forDigit((int)x & mask, radix);
               x >>>= shift;
            } while (x != 0L);
         } else {
    long quotient;
            if ((radix & 1) == 0) {
               quotient = (x >>> 1) / (radix >>> 1);
            } else {
               quotient = divide(x, radix);
            }

    long rem = x - quotient * radix;
            buf[--i] = char.forDigit((int)rem, radix);

            for (long var9 = quotient; var9 > 0L; var9 /= radix) {
               buf[--i] = char.forDigit((int)(var9 % radix), radix);
            }
         }

         return new std::string(buf, i, buf.length - i);
      }
   }

   static {
    BigInteger overflow = std::make_shared<BigInteger>("10000000000000000", 16);

      for (int i = 2; i <= 36; i++) {
         maxValueDivs[i] = divide(-1L, i);
         maxValueMods[i] = (int)remainder(-1L, i);
         maxSafeDigits[i] = overflow.toString(i).length() - 1;
      }
   }
}
} // namespace primitives
} // namespace common
} // namespace google
} // namespace com
