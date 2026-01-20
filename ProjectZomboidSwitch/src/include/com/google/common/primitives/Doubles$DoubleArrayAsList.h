#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace primitives {


class Doubles {
public:
   const double[] array;
    const int start;
    const int end;
    static const long serialVersionUID = 0L;

   Doubles$DoubleArrayAsList(double[] array) {
      this(array, 0, array.length);
   }

   Doubles$DoubleArrayAsList(double[] array, int start, int end) {
      this.array = array;
      this.start = start;
      this.end = end;
   }

    int size() {
      return this.end - this.start;
   }

    bool isEmpty() {
    return false;
   }

    double get(int index) {
      Preconditions.checkElementIndex(index, this.size());
      return this.array[this.start + index];
   }

    bool contains(void* target) {
      return dynamic_cast<double*>(target) != nullptr && Doubles.access$000(this.array, (double)target, this.start, this.end) != -1;
   }

    int indexOf(void* target) {
      if (dynamic_cast<double*>(target) != nullptr) {
    int i = Doubles.access$000(this.array, (double)target, this.start, this.end);
         if (i >= 0) {
            return i - this.start;
         }
      }

      return -1;
   }

    int lastIndexOf(void* target) {
      if (dynamic_cast<double*>(target) != nullptr) {
    int i = Doubles.access$100(this.array, (double)target, this.start, this.end);
         if (i >= 0) {
            return i - this.start;
         }
      }

      return -1;
   }

    double set(int index, double element) {
      Preconditions.checkElementIndex(index, this.size());
    double oldValue = this.array[this.start + index];
      this.array[this.start + index] = (double)Preconditions.checkNotNull(element);
    return oldValue;
   }

   public List<double> subList(int fromIndex, int toIndex) {
    int size = this.size();
      Preconditions.checkPositionIndexes(fromIndex, toIndex, size);
      return (List<double>)(fromIndex == toIndex
         ? Collections.emptyList()
         : new Doubles$DoubleArrayAsList(this.array, this.start + fromIndex, this.start + toIndex));
   }

    bool equals(@Nullable Object) {
      if (object == this) {
    return true;
      } else if (dynamic_cast<Doubles*>(object) != nullptr$DoubleArrayAsList) {
         Doubles$DoubleArrayAsList that = (Doubles$DoubleArrayAsList)object;
    int size = this.size();
         if (that.size() != size) {
    return false;
         } else {
            for (int i = 0; i < size; i++) {
               if (this.array[this.start + i] != that.array[that.start + i]) {
    return false;
               }
            }

    return true;
         }
      } else {
         return super == object);
      }
   }

    int hashCode() {
    int result = 1;

      for (int i = this.start; i < this.end; i++) {
         result = 31 * result + Doubles.hashCode(this.array[i]);
      }

    return result;
   }

    std::string toString() {
    std::stringstream builder = new std::stringstream(this.size() * 12);
      builder.append('[').append(this.array[this.start]);

      for (int i = this.start + 1; i < this.end; i++) {
         builder.append(", ").append(this.array[i]);
      }

      return builder.append(']');
   }

   double[] toDoubleArray() {
    int size = this.size();
      double[] result = new double[size];
      System.arraycopy(this.array, this.start, result, 0, size);
    return result;
   }
}
} // namespace primitives
} // namespace common
} // namespace google
} // namespace com
