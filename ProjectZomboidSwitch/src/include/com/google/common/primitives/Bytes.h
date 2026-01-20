#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/primitives/Bytes/ByteArrayAsList.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace primitives {


class Bytes {
public:
    private Bytes() {
   }

    static int hashCode(uint8_t value) {
    return value;
   }

    static bool contains(byte[] array, uint8_t target) {
    for (auto& value : array)         if (value == target) {
    return true;
         }
      }

    return false;
   }

    static int indexOf(byte[] array, uint8_t target) {
    return indexOf();
   }

    static int indexOf(byte[] array, uint8_t target, int start, int end) {
      for (int i = start; i < end; i++) {
         if (array[i] == target) {
    return i;
         }
      }

      return -1;
   }

    static int indexOf(byte[] array, byte[] target) {
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

    static int lastIndexOf(byte[] array, uint8_t target) {
    return lastIndexOf();
   }

    static int lastIndexOf(byte[] array, uint8_t target, int start, int end) {
      for (int i = end - 1; i >= start; i--) {
         if (array[i] == target) {
    return i;
         }
      }

      return -1;
   }

   public static byte[] concat(byte[]... arrays) {
    int length = 0;

      for (byte[] array : arrays) {
         length += array.length;
      }

      byte[] result = new byte[length];
    int pos = 0;

      for (byte[] array : arrays) {
         System.arraycopy(array, 0, result, pos, array.length);
         pos += array.length;
      }

    return result;
   }

   public static byte[] ensureCapacity(byte[] array, int minLength, int padding) {
      Preconditions.checkArgument(minLength >= 0, "Invalid minLength: %s", minLength);
      Preconditions.checkArgument(padding >= 0, "Invalid padding: %s", padding);
      return array.length < minLength ? Arrays.copyOf(array, minLength + padding) : array;
   }

   public static byte[] toArray(Collection<? : public Number> collection) {
      if (dynamic_cast<ByteArrayAsList*>(collection) != nullptr) {
         return ((ByteArrayAsList)collection).toByteArray();
      } else {
         Object[] boxedArray = collection.toArray();
    int len = boxedArray.length;
         byte[] array = new byte[len];

         for (int i = 0; i < len; i++) {
            array[i] = ((Number)Preconditions.checkNotNull(boxedArray[i])).byteValue();
         }

    return array;
      }
   }

   public static List<uint8_t> asList(byte... backingArray) {
      return (List<uint8_t>)(backingArray.length == 0 ? Collections.emptyList() : std::make_shared<ByteArrayAsList>(backingArray));
   }
}
} // namespace primitives
} // namespace common
} // namespace google
} // namespace com
