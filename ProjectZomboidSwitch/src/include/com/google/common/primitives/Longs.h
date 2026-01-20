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
#include "com/google/common/base/Converter.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/primitives/Longs/LexicographicalComparator.h"
#include "com/google/common/primitives/Longs/LongArrayAsList.h"
#include "com/google/common/primitives/Longs/LongConverter.h"
#include "javax/annotation/CheckForNull.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace primitives {


class Longs {
public:
    static const int BYTES = 8;
    static const long MAX_POWER_OF_TWO = 4611686018427387904L;
   private static const byte[] asciiDigits = createAsciiDigits();

    private Longs() {
   }

    static int hashCode(long value) {
      return (int)(value ^ value >>> 32);
   }

    static int compare(long a, long b) {
      return a < b ? -1 : (a > b ? 1 : 0);
   }

    static bool contains(long[] array, long target) {
    for (auto& value : array)         if (value == target) {
    return true;
         }
      }

    return false;
   }

    static int indexOf(long[] array, long target) {
    return indexOf();
   }

    static int indexOf(long[] array, long target, int start, int end) {
      for (int i = start; i < end; i++) {
         if (array[i] == target) {
    return i;
         }
      }

      return -1;
   }

    static int indexOf(long[] array, long[] target) {
      Preconditions.checkNotNull(array, "array");
      Preconditions.checkNotNull(target, "target");
      if (target.length == 0) {
    return 0;
      } else {
         label28:
         for (int i = 0; i < array.length - target.length + 1; i++) {
            for (int j = 0; j < target.length; j++) {
               if (array[i + j] != target[j]) {
    continue label28;
               }
            }

    return i;
         }

         return -1;
      }
   }

    static int lastIndexOf(long[] array, long target) {
    return lastIndexOf();
   }

    static int lastIndexOf(long[] array, long target, int start, int end) {
      for (int i = end - 1; i >= start; i--) {
         if (array[i] == target) {
    return i;
         }
      }

      return -1;
   }

    static long min(long... array) {
      Preconditions.checkArgument(array.length > 0);
    long min = array[0];

      for (int i = 1; i < array.length; i++) {
         if (array[i] < min) {
            min = array[i];
         }
      }

    return min;
   }

    static long max(long... array) {
      Preconditions.checkArgument(array.length > 0);
    long max = array[0];

      for (int i = 1; i < array.length; i++) {
         if (array[i] > max) {
            max = array[i];
         }
      }

    return max;
   }

   public static long[] concat(long[]... arrays) {
    int length = 0;

      for (long[] array : arrays) {
         length += array.length;
      }

      long[] result = new long[length];
    int pos = 0;

      for (long[] array : arrays) {
         System.arraycopy(array, 0, result, pos, array.length);
         pos += array.length;
      }

    return result;
   }

   public static byte[] toByteArray(long value) {
      byte[] result = new byte[8];

      for (int i = 7; i >= 0; i--) {
         result[i] = (byte)(value & 255L);
         value >>= 8;
      }

    return result;
   }

    static long fromByteArray(byte[] bytes) {
      Preconditions.checkArgument(bytes.length >= 8, "array too small: %s < %s", bytes.length, 8);
    return fromBytes();
   }

    static long fromBytes(uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4, uint8_t b5, uint8_t b6, uint8_t b7, uint8_t b8) {
      return (b1 & 255L) << 56
         | (b2 & 255L) << 48
         | (b3 & 255L) << 40
         | (b4 & 255L) << 32
         | (b5 & 255L) << 24
         | (b6 & 255L) << 16
         | (b7 & 255L) << 8
         | b8 & 255L;
   }

   private static byte[] createAsciiDigits() {
      byte[] result = new byte[128];
      Arrays.fill(result, (byte)-1);

      for (int i = 0; i <= 9; i++) {
         result[48 + i] = (byte)i;
      }

      for (int i = 0; i <= 26; i++) {
         result[65 + i] = (byte)(10 + i);
         result[97 + i] = (byte)(10 + i);
      }

    return result;
   }

    static int digit(char c) {
      return c < 128 ? asciiDigits[c] : -1;
   }

    static long tryParse(const std::string& string) {
    return tryParse();
   }

    static long tryParse(const std::string& string, int radix) {
      if (((std::string)Preconditions.checkNotNull(string)).empty()) {
    return nullptr;
      } else if (radix >= 2 && radix <= 36) {
    bool negative = string.charAt(0) == '-';
    int index = negative ? 1 : 0;
         if (index == string.length()) {
    return nullptr;
         } else {
    int digit = digit(string.charAt(index++));
            if (digit >= 0 && digit < radix) {
    long accum = -digit;
    long cap = int64_t.MIN_VALUE / radix;

               while (index < string.length()) {
                  digit = digit(string.charAt(index++));
                  if (digit < 0 || digit >= radix || accum < cap) {
    return nullptr;
                  }

                  accum *= radix;
                  if (accum < int64_t.MIN_VALUE + digit) {
    return nullptr;
                  }

                  accum -= digit;
               }

               if (negative) {
    return accum;
               } else {
    return accum = = int64_t.MIN_VALUE ? nullptr : -accum;
               }
            } else {
    return nullptr;
            }
         }
      } else {
         throw IllegalArgumentException("radix must be between MIN_RADIX and MAX_RADIX but was " + radix);
      }
   }

   public static Converter<std::string, int64_t> stringConverter() {
      return LongConverter.INSTANCE;
   }

   public static long[] ensureCapacity(long[] array, int minLength, int padding) {
      Preconditions.checkArgument(minLength >= 0, "Invalid minLength: %s", minLength);
      Preconditions.checkArgument(padding >= 0, "Invalid padding: %s", padding);
      return array.length < minLength ? Arrays.copyOf(array, minLength + padding) : array;
   }

    static std::string join(const std::string& separator, long... array) {
      Preconditions.checkNotNull(separator);
      if (array.length == 0) {
         return "";
      } else {
    std::stringstream builder = new std::stringstream(array.length * 10);
         builder.append(array[0]);

         for (int i = 1; i < array.length; i++) {
            builder.append(separator).append(array[i]);
         }

         return builder;
      }
   }

   public static Comparator<long[]> lexicographicalComparator() {
      return LexicographicalComparator.INSTANCE;
   }

   public static long[] toArray(Collection<? : public Number> collection) {
      if (dynamic_cast<LongArrayAsList*>(collection) != nullptr) {
         return ((LongArrayAsList)collection).toLongArray();
      } else {
         Object[] boxedArray = collection.toArray();
    int len = boxedArray.length;
         long[] array = new long[len];

         for (int i = 0; i < len; i++) {
            array[i] = ((Number)Preconditions.checkNotNull(boxedArray[i])).longValue();
         }

    return array;
      }
   }

   public static List<int64_t> asList(long... backingArray) {
      return (List<int64_t>)(backingArray.length == 0 ? Collections.emptyList() : std::make_shared<LongArrayAsList>(backingArray));
   }
}
} // namespace primitives
} // namespace common
} // namespace google
} // namespace com
