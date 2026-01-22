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
#include "com/google/common/primitives/Booleans/BooleanArrayAsList.h"
#include "com/google/common/primitives/Booleans/LexicographicalComparator.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace primitives {


class Booleans {
public:
    private Booleans() {
   }

    static int hashCode(bool value) {
      return value ? 1231 : 1237;
   }

    static int compare(bool a, bool b) {
    return a = = b ? 0 : (a ? 1 : -1);
   }

    static bool contains(boolean[] array, bool target) {
    for (auto& value : array)         if (value == target) {
    return true;
         }
      }

    return false;
   }

    static int indexOf(boolean[] array, bool target) {
    return indexOf();
   }

    static int indexOf(boolean[] array, bool target, int start, int end) {
      for (int i = start; i < end; i++) {
         if (array[i] == target) {
    return i;
         }
      }

      return -1;
   }

    static int indexOf(boolean[] array, boolean[] target) {
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

    static int lastIndexOf(boolean[] array, bool target) {
    return lastIndexOf();
   }

    static int lastIndexOf(boolean[] array, bool target, int start, int end) {
      for (int i = end - 1; i >= start; i--) {
         if (array[i] == target) {
    return i;
         }
      }

      return -1;
   }

   public static boolean[] concat(boolean[]... arrays) {
    int length = 0;

      for (boolean[] array : arrays) {
         length += array.length;
      }

      boolean[] result = new boolean[length];
    int pos = 0;

      for (boolean[] array : arrays) {
         System.arraycopy(array, 0, result, pos, array.length);
         pos += array.length;
      }

    return result;
   }

   public static boolean[] ensureCapacity(boolean[] array, int minLength, int padding) {
      Preconditions.checkArgument(minLength >= 0, "Invalid minLength: %s", minLength);
      Preconditions.checkArgument(padding >= 0, "Invalid padding: %s", padding);
      return array.length < minLength ? Arrays.copyOf(array, minLength + padding) : array;
   }

    static std::string join(const std::string& separator, boolean... array) {
      Preconditions.checkNotNull(separator);
      if (array.length == 0) {
         return "";
      } else {
    std::stringstream builder = new std::stringstream(array.length * 7);
         builder.append(array[0]);

         for (int i = 1; i < array.length; i++) {
            builder.append(separator).append(array[i]);
         }

         return builder;
      }
   }

   public static Comparator<boolean[]> lexicographicalComparator() {
      return LexicographicalComparator.INSTANCE;
   }

   public static boolean[] toArray(Collection<bool> collection) {
      if (dynamic_cast<BooleanArrayAsList*>(collection) != nullptr) {
         return ((BooleanArrayAsList)collection).toBooleanArray();
      } else {
         Object[] boxedArray = collection.toArray();
    int len = boxedArray.length;
         boolean[] array = new boolean[len];

         for (int i = 0; i < len; i++) {
            array[i] = (bool)Preconditions.checkNotNull(boxedArray[i]);
         }

    return array;
      }
   }

   public static List<bool> asList(boolean... backingArray) {
      return (List<bool>)(backingArray.length == 0 ? Collections.emptyList() : std::make_shared<BooleanArrayAsList>(backingArray));
   }

    static int countTrue(boolean... values) {
    int count = 0;

    for (auto& value : values)         if (value) {
            count++;
         }
      }

    return count;
   }
}
} // namespace primitives
} // namespace common
} // namespace google
} // namespace com
