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
#include "com/google/common/primitives/Floats/FloatArrayAsList.h"
#include "com/google/common/primitives/Floats/FloatConverter.h"
#include "com/google/common/primitives/Floats/LexicographicalComparator.h"
#include "javax/annotation/CheckForNull.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace primitives {


class Floats {
public:
    static const int BYTES = 4;

    private Floats() {
   }

    static int hashCode(float value) {
      return float.valueOf(value).hashCode();
   }

    static int compare(float a, float b) {
      return float.compare(a, b);
   }

    static bool isFinite(float value) {
      return float.NEGATIVE_INFINITY < value & value < float.POSITIVE_INFINITY;
   }

    static bool contains(float[] array, float target) {
    for (auto& value : array)         if (value == target) {
    return true;
         }
      }

    return false;
   }

    static int indexOf(float[] array, float target) {
    return indexOf();
   }

    static int indexOf(float[] array, float target, int start, int end) {
      for (int i = start; i < end; i++) {
         if (array[i] == target) {
    return i;
         }
      }

      return -1;
   }

    static int indexOf(float[] array, float[] target) {
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

    static int lastIndexOf(float[] array, float target) {
    return lastIndexOf();
   }

    static int lastIndexOf(float[] array, float target, int start, int end) {
      for (int i = end - 1; i >= start; i--) {
         if (array[i] == target) {
    return i;
         }
      }

      return -1;
   }

    static float min(float... array) {
      Preconditions.checkArgument(array.length > 0);
    float min = array[0];

      for (int i = 1; i < array.length; i++) {
         min = Math.min(min, array[i]);
      }

    return min;
   }

    static float max(float... array) {
      Preconditions.checkArgument(array.length > 0);
    float max = array[0];

      for (int i = 1; i < array.length; i++) {
         max = Math.max(max, array[i]);
      }

    return max;
   }

   public static float[] concat(float[]... arrays) {
    int length = 0;

      for (float[] array : arrays) {
         length += array.length;
      }

      float[] result = new float[length];
    int pos = 0;

      for (float[] array : arrays) {
         System.arraycopy(array, 0, result, pos, array.length);
         pos += array.length;
      }

    return result;
   }

   public static Converter<std::string, float> stringConverter() {
      return FloatConverter.INSTANCE;
   }

   public static float[] ensureCapacity(float[] array, int minLength, int padding) {
      Preconditions.checkArgument(minLength >= 0, "Invalid minLength: %s", minLength);
      Preconditions.checkArgument(padding >= 0, "Invalid padding: %s", padding);
      return array.length < minLength ? Arrays.copyOf(array, minLength + padding) : array;
   }

    static std::string join(const std::string& separator, float... array) {
      Preconditions.checkNotNull(separator);
      if (array.length == 0) {
         return "";
      } else {
    std::stringstream builder = new std::stringstream(array.length * 12);
         builder.append(array[0]);

         for (int i = 1; i < array.length; i++) {
            builder.append(separator).append(array[i]);
         }

         return builder;
      }
   }

   public static Comparator<float[]> lexicographicalComparator() {
      return LexicographicalComparator.INSTANCE;
   }

   public static float[] toArray(Collection<? : public Number> collection) {
      if (dynamic_cast<FloatArrayAsList*>(collection) != nullptr) {
         return ((FloatArrayAsList)collection).toFloatArray();
      } else {
         Object[] boxedArray = collection.toArray();
    int len = boxedArray.length;
         float[] array = new float[len];

         for (int i = 0; i < len; i++) {
            array[i] = ((Number)Preconditions.checkNotNull(boxedArray[i])).floatValue();
         }

    return array;
      }
   }

   public static List<float> asList(float... backingArray) {
      return (List<float>)(backingArray.length == 0 ? Collections.emptyList() : std::make_shared<FloatArrayAsList>(backingArray));
   }

    static float tryParse(const std::string& string) {
      if (Doubles.FLOATING_POINT_PATTERN.matcher(string).matches()) {
         try {
            return float.parseFloat(string);
         } catch (NumberFormatException var2) {
         }
      }

    return nullptr;
   }
}
} // namespace primitives
} // namespace common
} // namespace google
} // namespace com
