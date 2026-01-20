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
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Converter.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/primitives/Ints/IntArrayAsList.h"
#include "com/google/common/primitives/Ints/IntConverter.h"
#include "com/google/common/primitives/Ints/LexicographicalComparator.h"
#include "javax/annotation/CheckForNull.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace primitives {


class Ints {
public:
    static const int BYTES = 4;
    static const int MAX_POWER_OF_TWO = 1073741824;

    private Ints() {
   }

    static int hashCode(int value) {
    return value;
   }

    static int checkedCast(long value) {
    int result = (int)value;
      if (result != value) {
         throw IllegalArgumentException("Out of range: " + value);
      } else {
    return result;
      }
   }

    static int saturatedCast(long value) {
      if (value > 2147483647L) {
         return int.MAX_VALUE;
      } else {
         return value < -2147483648L ? int.MIN_VALUE : (int)value;
      }
   }

    static int compare(int a, int b) {
      return a < b ? -1 : (a > b ? 1 : 0);
   }

    static bool contains(int[] array, int target) {
    for (auto& value : array)         if (value == target) {
    return true;
         }
      }

    return false;
   }

    static int indexOf(int[] array, int target) {
    return indexOf();
   }

    static int indexOf(int[] array, int target, int start, int end) {
      for (int i = start; i < end; i++) {
         if (array[i] == target) {
    return i;
         }
      }

      return -1;
   }

    static int indexOf(int[] array, int[] target) {
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

    static int lastIndexOf(int[] array, int target) {
    return lastIndexOf();
   }

    static int lastIndexOf(int[] array, int target, int start, int end) {
      for (int i = end - 1; i >= start; i--) {
         if (array[i] == target) {
    return i;
         }
      }

      return -1;
   }

    static int min(int... array) {
      Preconditions.checkArgument(array.length > 0);
    int min = array[0];

      for (int i = 1; i < array.length; i++) {
         if (array[i] < min) {
            min = array[i];
         }
      }

    return min;
   }

    static int max(int... array) {
      Preconditions.checkArgument(array.length > 0);
    int max = array[0];

      for (int i = 1; i < array.length; i++) {
         if (array[i] > max) {
            max = array[i];
         }
      }

    return max;
   }

   public static int[] concat(int[]... arrays) {
    int length = 0;

      for (int[] array : arrays) {
         length += array.length;
      }

      int[] result = new int[length];
    int pos = 0;

      for (int[] array : arrays) {
         System.arraycopy(array, 0, result, pos, array.length);
         pos += array.length;
      }

    return result;
   }

   public static byte[] toByteArray(int value) {
      return new byte[]{(byte)(value >> 24), (byte)(value >> 16), (byte)(value >> 8), (byte)value};
   }

    static int fromByteArray(byte[] bytes) {
      Preconditions.checkArgument(bytes.length >= 4, "array too small: %s < %s", bytes.length, 4);
    return fromBytes();
   }

    static int fromBytes(uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4) {
      return b1 << 24 | (b2 & 0xFF) << 16 | (b3 & 0xFF) << 8 | b4 & 0xFF;
   }

   public static Converter<std::string, int> stringConverter() {
      return IntConverter.INSTANCE;
   }

   public static int[] ensureCapacity(int[] array, int minLength, int padding) {
      Preconditions.checkArgument(minLength >= 0, "Invalid minLength: %s", minLength);
      Preconditions.checkArgument(padding >= 0, "Invalid padding: %s", padding);
      return array.length < minLength ? Arrays.copyOf(array, minLength + padding) : array;
   }

    static std::string join(const std::string& separator, int... array) {
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

   public static Comparator<int[]> lexicographicalComparator() {
      return LexicographicalComparator.INSTANCE;
   }

   public static int[] toArray(Collection<? : public Number> collection) {
      if (dynamic_cast<IntArrayAsList*>(collection) != nullptr) {
         return ((IntArrayAsList)collection).toIntArray();
      } else {
         Object[] boxedArray = collection.toArray();
    int len = boxedArray.length;
         int[] array = new int[len];

         for (int i = 0; i < len; i++) {
            array[i] = ((Number)Preconditions.checkNotNull(boxedArray[i])).intValue();
         }

    return array;
      }
   }

   public static List<int> asList(int... backingArray) {
      return (List<int>)(backingArray.length == 0 ? Collections.emptyList() : std::make_shared<IntArrayAsList>(backingArray));
   }

    static int tryParse(const std::string& string) {
    return tryParse();
   }

    static int tryParse(const std::string& string, int radix) {
    long result = Longs.tryParse(string, radix);
      return result != nullptr && result == result.intValue() ? result.intValue() : nullptr;
   }
}
} // namespace primitives
} // namespace common
} // namespace google
} // namespace com
