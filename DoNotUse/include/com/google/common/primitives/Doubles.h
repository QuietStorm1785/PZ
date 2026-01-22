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
#include "com/google/common/primitives/Doubles/DoubleArrayAsList.h"
#include "com/google/common/primitives/Doubles/DoubleConverter.h"
#include "com/google/common/primitives/Doubles/LexicographicalComparator.h"
#include "javax/annotation/CheckForNull.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace primitives {


class Doubles {
public:
    static const int BYTES = 8;
    static const Pattern FLOATING_POINT_PATTERN = fpPattern();

    private Doubles() {
   }

    static int hashCode(double value) {
      return double.valueOf(value).hashCode();
   }

    static int compare(double a, double b) {
      return double.compare(a, b);
   }

    static bool isFinite(double value) {
      return double.NEGATIVE_INFINITY < value & value < double.POSITIVE_INFINITY;
   }

    static bool contains(double[] array, double target) {
    for (auto& value : array)         if (value == target) {
    return true;
         }
      }

    return false;
   }

    static int indexOf(double[] array, double target) {
    return indexOf();
   }

    static int indexOf(double[] array, double target, int start, int end) {
      for (int i = start; i < end; i++) {
         if (array[i] == target) {
    return i;
         }
      }

      return -1;
   }

    static int indexOf(double[] array, double[] target) {
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

    static int lastIndexOf(double[] array, double target) {
    return lastIndexOf();
   }

    static int lastIndexOf(double[] array, double target, int start, int end) {
      for (int i = end - 1; i >= start; i--) {
         if (array[i] == target) {
    return i;
         }
      }

      return -1;
   }

    static double min(double... array) {
      Preconditions.checkArgument(array.length > 0);
    double min = array[0];

      for (int i = 1; i < array.length; i++) {
         min = Math.min(min, array[i]);
      }

    return min;
   }

    static double max(double... array) {
      Preconditions.checkArgument(array.length > 0);
    double max = array[0];

      for (int i = 1; i < array.length; i++) {
         max = Math.max(max, array[i]);
      }

    return max;
   }

   public static double[] concat(double[]... arrays) {
    int length = 0;

      for (double[] array : arrays) {
         length += array.length;
      }

      double[] result = new double[length];
    int pos = 0;

      for (double[] array : arrays) {
         System.arraycopy(array, 0, result, pos, array.length);
         pos += array.length;
      }

    return result;
   }

   public static Converter<std::string, double> stringConverter() {
      return DoubleConverter.INSTANCE;
   }

   public static double[] ensureCapacity(double[] array, int minLength, int padding) {
      Preconditions.checkArgument(minLength >= 0, "Invalid minLength: %s", minLength);
      Preconditions.checkArgument(padding >= 0, "Invalid padding: %s", padding);
      return array.length < minLength ? Arrays.copyOf(array, minLength + padding) : array;
   }

    static std::string join(const std::string& separator, double... array) {
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

   public static Comparator<double[]> lexicographicalComparator() {
      return LexicographicalComparator.INSTANCE;
   }

   public static double[] toArray(Collection<? : public Number> collection) {
      if (dynamic_cast<DoubleArrayAsList*>(collection) != nullptr) {
         return ((DoubleArrayAsList)collection).toDoubleArray();
      } else {
         Object[] boxedArray = collection.toArray();
    int len = boxedArray.length;
         double[] array = new double[len];

         for (int i = 0; i < len; i++) {
            array[i] = ((Number)Preconditions.checkNotNull(boxedArray[i])).doubleValue();
         }

    return array;
      }
   }

   public static List<double> asList(double... backingArray) {
      return (List<double>)(backingArray.length == 0 ? Collections.emptyList() : std::make_shared<DoubleArrayAsList>(backingArray));
   }

    static Pattern fpPattern() {
    std::string decimal = "(?:\\d++(?:\\.\\d*+)?|\\.\\d++)";
    std::string completeDec = decimal + "(?:[eE][+-]?\\d++)?[fFdD]?";
    std::string hex = "(?:\\p{XDigit}++(?:\\.\\p{XDigit}*+)?|\\.\\p{XDigit}++)";
    std::string completeHex = "0[xX]" + hex + "[pP][+-]?\\d++[fFdD]?";
    std::string fpPattern = "[+-]?(?:NaN|Infinity|" + completeDec + "|" + completeHex + ")";
      return Pattern.compile(fpPattern);
   }

    static double tryParse(const std::string& string) {
      if (FLOATING_POINT_PATTERN.matcher(string).matches()) {
         try {
            return double.parseDouble(string);
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
