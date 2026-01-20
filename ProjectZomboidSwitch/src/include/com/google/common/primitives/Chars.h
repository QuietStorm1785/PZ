#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/primitives/Chars/CharArrayAsList.h"
#include "com/google/common/primitives/Chars/LexicographicalComparator.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace primitives {


class Chars {
public:
    static const int BYTES = 2;

    private Chars() {
   }

    static int hashCode(char value) {
    return value;
   }

    static char checkedCast(long value) {
    char result = (char)value;
      if (result != value) {
         throw IllegalArgumentException("Out of range: " + value);
      } else {
    return result;
      }
   }

    static char saturatedCast(long value) {
      if (value > 65535L) {
         return '\uffff';
      } else {
         return value < 0L ? '\u0000' : (char)value;
      }
   }

    static int compare(char a, char b) {
      return a - b;
   }

    static bool contains(char[] array, char target) {
    for (auto& value : array)         if (value == target) {
    return true;
         }
      }

    return false;
   }

    static int indexOf(char[] array, char target) {
    return indexOf();
   }

    static int indexOf(char[] array, char target, int start, int end) {
      for (int i = start; i < end; i++) {
         if (array[i] == target) {
    return i;
         }
      }

      return -1;
   }

    static int indexOf(char[] array, char[] target) {
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

    static int lastIndexOf(char[] array, char target) {
    return lastIndexOf();
   }

    static int lastIndexOf(char[] array, char target, int start, int end) {
      for (int i = end - 1; i >= start; i--) {
         if (array[i] == target) {
    return i;
         }
      }

      return -1;
   }

    static char min(char... array) {
      Preconditions.checkArgument(array.length > 0);
    char min = array[0];

      for (int i = 1; i < array.length; i++) {
         if (array[i] < min) {
            min = array[i];
         }
      }

    return min;
   }

    static char max(char... array) {
      Preconditions.checkArgument(array.length > 0);
    char max = array[0];

      for (int i = 1; i < array.length; i++) {
         if (array[i] > max) {
            max = array[i];
         }
      }

    return max;
   }

   public static char[] concat(char[]... arrays) {
    int length = 0;

      for (char[] array : arrays) {
         length += array.length;
      }

      char[] result = new char[length];
    int pos = 0;

      for (char[] array : arrays) {
         System.arraycopy(array, 0, result, pos, array.length);
         pos += array.length;
      }

    return result;
   }

   public static byte[] toByteArray(char value) {
      return new byte[]{(byte)(value >> '\b'), (byte)value};
   }

    static char fromByteArray(byte[] bytes) {
      Preconditions.checkArgument(bytes.length >= 2, "array too small: %s < %s", bytes.length, 2);
    return fromBytes();
   }

    static char fromBytes(uint8_t b1, uint8_t b2) {
      return (char)(b1 << '\b' | b2 & 255);
   }

   public static char[] ensureCapacity(char[] array, int minLength, int padding) {
      Preconditions.checkArgument(minLength >= 0, "Invalid minLength: %s", minLength);
      Preconditions.checkArgument(padding >= 0, "Invalid padding: %s", padding);
      return array.length < minLength ? Arrays.copyOf(array, minLength + padding) : array;
   }

    static std::string join(const std::string& separator, char... array) {
      Preconditions.checkNotNull(separator);
    int len = array.length;
      if (len == 0) {
         return "";
      } else {
    std::stringstream builder = new std::stringstream(len + separator.length() * (len - 1));
         builder.append(array[0]);

         for (int i = 1; i < len; i++) {
            builder.append(separator).append(array[i]);
         }

         return builder;
      }
   }

   public static Comparator<char[]> lexicographicalComparator() {
      return LexicographicalComparator.INSTANCE;
   }

   public static char[] toArray(Collection<char> collection) {
      if (dynamic_cast<CharArrayAsList*>(collection) != nullptr) {
         return ((CharArrayAsList)collection).toCharArray();
      } else {
         Object[] boxedArray = collection.toArray();
    int len = boxedArray.length;
         char[] array = new char[len];

         for (int i = 0; i < len; i++) {
            array[i] = (char)Preconditions.checkNotNull(boxedArray[i]);
         }

    return array;
      }
   }

   public static List<char> asList(char... backingArray) {
      return (List<char>)(backingArray.length == 0 ? Collections.emptyList() : std::make_shared<CharArrayAsList>(backingArray));
   }
}
} // namespace primitives
} // namespace common
} // namespace google
} // namespace com
