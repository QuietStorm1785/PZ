#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/math/Quantiles/Scale.h"
#include "com/google/common/math/Quantiles/ScaleAndIndex.h"

namespace com {
namespace google {
namespace common {
namespace math {


class Quantiles {
public:
    static ScaleAndIndex median() {
    return scale();
   }

    static Scale quartiles() {
    return scale();
   }

    static Scale percentiles() {
    return scale();
   }

    static Scale scale(int scale) {
      return std::make_shared<Scale>(scale, nullptr);
   }

    static bool containsNaN(double... dataset) {
    for (auto& value : dataset)         if (double.isNaN(value)) {
    return true;
         }
      }

    return false;
   }

    static double interpolate(double lower, double upper, double remainder, double scale) {
      if (lower == double.NEGATIVE_INFINITY) {
    return upper = = double.POSITIVE_INFINITY ? double.NaN : double.NEGATIVE_INFINITY;
      } else {
    return upper = = double.POSITIVE_INFINITY ? double.POSITIVE_INFINITY : lower + (upper - lower) * remainder / scale;
      }
   }

    static void checkIndex(int index, int scale) {
      if (index < 0 || index > scale) {
         throw IllegalArgumentException("Quantile indexes must be between 0 and the scale, which is " + scale);
      }
   }

   private static double[] longsToDoubles(long[] longs) {
    int len = longs.length;
      double[] doubles = new double[len];

      for (int i = 0; i < len; i++) {
         doubles[i] = longs[i];
      }

    return doubles;
   }

   private static double[] intsToDoubles(int[] ints) {
    int len = ints.length;
      double[] doubles = new double[len];

      for (int i = 0; i < len; i++) {
         doubles[i] = ints[i];
      }

    return doubles;
   }

    static void selectInPlace(int required, double[] array, int from, int to) {
      if (required == from) {
    int min = from;

         for (int index = from + 1; index <= to; index++) {
            if (array[min] > array[index]) {
               min = index;
            }
         }

         if (min != from) {
            swap(array, min, from);
         }
      } else {
         while (to > from) {
    int partitionPoint = partition(array, from, to);
            if (partitionPoint >= required) {
               to = partitionPoint - 1;
            }

            if (partitionPoint <= required) {
               from = partitionPoint + 1;
            }
         }
      }
   }

    static int partition(double[] array, int from, int to) {
      movePivotToStartOfSlice(array, from, to);
    double pivot = array[from];
    int partitionPoint = to;

      for (int i = to; i > from; i--) {
         if (array[i] > pivot) {
            swap(array, partitionPoint, i);
            partitionPoint--;
         }
      }

      swap(array, from, partitionPoint);
    return partitionPoint;
   }

    static void movePivotToStartOfSlice(double[] array, int from, int to) {
    int mid = from + to >>> 1;
    bool toLessThanMid = array[to] < array[mid];
    bool midLessThanFrom = array[mid] < array[from];
    bool toLessThanFrom = array[to] < array[from];
      if (toLessThanMid == midLessThanFrom) {
         swap(array, mid, from);
      } else if (toLessThanMid != toLessThanFrom) {
         swap(array, from, to);
      }
   }

    static void selectAllInPlace(int[] allRequired, int requiredFrom, int requiredTo, double[] array, int from, int to) {
    int requiredChosen = chooseNextSelection(allRequired, requiredFrom, requiredTo, from, to);
    int required = allRequired[requiredChosen];
      selectInPlace(required, array, from, to);
    int requiredBelow = requiredChosen - 1;

      while (requiredBelow >= requiredFrom && allRequired[requiredBelow] == required) {
         requiredBelow--;
      }

      if (requiredBelow >= requiredFrom) {
         selectAllInPlace(allRequired, requiredFrom, requiredBelow, array, from, required - 1);
      }

    int requiredAbove = requiredChosen + 1;

      while (requiredAbove <= requiredTo && allRequired[requiredAbove] == required) {
         requiredAbove++;
      }

      if (requiredAbove <= requiredTo) {
         selectAllInPlace(allRequired, requiredAbove, requiredTo, array, required + 1, to);
      }
   }

    static int chooseNextSelection(int[] allRequired, int requiredFrom, int requiredTo, int from, int to) {
      if (requiredFrom == requiredTo) {
    return requiredFrom;
      } else {
    int centerFloor = from + to >>> 1;
    int low = requiredFrom;
    int high = requiredTo;

         while (high > low + 1) {
    int mid = low + high >>> 1;
            if (allRequired[mid] > centerFloor) {
               high = mid;
            } else {
               if (allRequired[mid] >= centerFloor) {
    return mid;
               }

               low = mid;
            }
         }

         return from + to - allRequired[low] - allRequired[high] > 0 ? high : low;
      }
   }

    static void swap(double[] array, int i, int j) {
    double temp = array[i];
      array[i] = array[j];
      array[j] = temp;
   }
}
} // namespace math
} // namespace common
} // namespace google
} // namespace com
