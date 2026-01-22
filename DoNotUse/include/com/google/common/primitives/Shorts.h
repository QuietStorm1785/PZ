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
#include "com/google/common/primitives/Shorts/LexicographicalComparator.h"
#include "com/google/common/primitives/Shorts/ShortArrayAsList.h"
#include "com/google/common/primitives/Shorts/ShortConverter.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace primitives {


class Shorts {
public:
    static const int BYTES = 2;
    static const short MAX_POWER_OF_TWO = 16384;

    private Shorts() {
   }

    static int hashCode(short value) {
    return value;
   }

    static short checkedCast(long value) {
    short result = (short)value;
      if (result != value) {
         throw IllegalArgumentException("Out of range: " + value);
      } else {
    return result;
      }
   }

    static short saturatedCast(long value) {
      if (value > 32767L) {
    return 32767;
      } else {
         return value < -32768L ? -32768 : (short)value;
      }
   }

    static int compare(short a, short b) {
      return a - b;
   }

    static bool contains(short[] array, short target) {
    for (auto& value : array)         if (value == target) {
    return true;
         }
      }

    return false;
   }

    static int indexOf(short[] array, short target) {
    return indexOf();
   }

    static int indexOf(short[] array, short target, int start, int end) {
      for (int i = start; i < end; i++) {
         if (array[i] == target) {
    return i;
         }
      }

      return -1;
   }

    static int indexOf(short[] array, short[] target) {
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

    static int lastIndexOf(short[] array, short target) {
    return lastIndexOf();
   }

    static int lastIndexOf(short[] array, short target, int start, int end) {
      for (int i = end - 1; i >= start; i--) {
         if (array[i] == target) {
    return i;
         }
      }

      return -1;
   }

    static short min(short... array) {
      Preconditions.checkArgument(array.length > 0);
    short min = array[0];

      for (int i = 1; i < array.length; i++) {
         if (array[i] < min) {
            min = array[i];
         }
      }

    return min;
   }

    static short max(short... array) {
      Preconditions.checkArgument(array.length > 0);
    short max = array[0];

      for (int i = 1; i < array.length; i++) {
         if (array[i] > max) {
            max = array[i];
         }
      }

    return max;
   }

   public static short[] concat(short[]... arrays) {
    int length = 0;

      for (short[] array : arrays) {
         length += array.length;
      }

      short[] result = new short[length];
    int pos = 0;

      for (short[] array : arrays) {
         System.arraycopy(array, 0, result, pos, array.length);
         pos += array.length;
      }

    return result;
   }

   public static byte[] toByteArray(short value) {
      return new byte[]{(byte)(value >> 8), (byte)value};
   }

    static short fromByteArray(byte[] bytes) {
      Preconditions.checkArgument(bytes.length >= 2, "array too small: %s < %s", bytes.length, 2);
    return fromBytes();
   }

    static short fromBytes(uint8_t b1, uint8_t b2) {
      return (short)(b1 << 8 | b2 & 255);
   }

   public static Converter<std::string, int16_t> stringConverter() {
      return ShortConverter.INSTANCE;
   }

   public static short[] ensureCapacity(short[] array, int minLength, int padding) {
      Preconditions.checkArgument(minLength >= 0, "Invalid minLength: %s", minLength);
      Preconditions.checkArgument(padding >= 0, "Invalid padding: %s", padding);
      return array.length < minLength ? Arrays.copyOf(array, minLength + padding) : array;
   }

    static std::string join(const std::string& separator, short... array) {
      Preconditions.checkNotNull(separator);
      if (array.length == 0) {
         return "";
      } else {
    std::stringstream builder = new std::stringstream(array.length * 6);
         builder.append(array[0]);

         for (int i = 1; i < array.length; i++) {
            builder.append(separator).append(array[i]);
         }

         return builder;
      }
   }

   public static Comparator<short[]> lexicographicalComparator() {
      return LexicographicalComparator.INSTANCE;
   }

   public static short[] toArray(Collection<? : public Number> collection) {
      if (dynamic_cast<ShortArrayAsList*>(collection) != nullptr) {
         return ((ShortArrayAsList)collection).toShortArray();
      } else {
         Object[] boxedArray = collection.toArray();
    int len = boxedArray.length;
         short[] array = new short[len];

         for (int i = 0; i < len; i++) {
            array[i] = ((Number)Preconditions.checkNotNull(boxedArray[i])).shortValue();
         }

    return array;
      }
   }

   public static List<int16_t> asList(short... backingArray) {
      return (List<int16_t>)(backingArray.length == 0 ? Collections.emptyList() : std::make_shared<ShortArrayAsList>(backingArray));
   }
}
} // namespace primitives
} // namespace common
} // namespace google
} // namespace com
