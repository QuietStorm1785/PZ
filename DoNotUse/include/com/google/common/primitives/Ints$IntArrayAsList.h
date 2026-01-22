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


class Ints {
public:
   const int[] array;
    const int start;
    const int end;
    static const long serialVersionUID = 0L;

   Ints$IntArrayAsList(int[] array) {
      this(array, 0, array.length);
   }

   Ints$IntArrayAsList(int[] array, int start, int end) {
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

    int get(int index) {
      Preconditions.checkElementIndex(index, this.size());
      return this.array[this.start + index];
   }

    bool contains(void* target) {
      return dynamic_cast<int*>(target) != nullptr && Ints.access$000(this.array, (int)target, this.start, this.end) != -1;
   }

    int indexOf(void* target) {
      if (dynamic_cast<int*>(target) != nullptr) {
    int i = Ints.access$000(this.array, (int)target, this.start, this.end);
         if (i >= 0) {
            return i - this.start;
         }
      }

      return -1;
   }

    int lastIndexOf(void* target) {
      if (dynamic_cast<int*>(target) != nullptr) {
    int i = Ints.access$100(this.array, (int)target, this.start, this.end);
         if (i >= 0) {
            return i - this.start;
         }
      }

      return -1;
   }

    int set(int index, int element) {
      Preconditions.checkElementIndex(index, this.size());
    int oldValue = this.array[this.start + index];
      this.array[this.start + index] = (int)Preconditions.checkNotNull(element);
    return oldValue;
   }

   public List<int> subList(int fromIndex, int toIndex) {
    int size = this.size();
      Preconditions.checkPositionIndexes(fromIndex, toIndex, size);
      return (List<int>)(fromIndex == toIndex ? Collections.emptyList() : new Ints$IntArrayAsList(this.array, this.start + fromIndex, this.start + toIndex));
   }

    bool equals(@Nullable Object) {
      if (object == this) {
    return true;
      } else if (dynamic_cast<Ints*>(object) != nullptr$IntArrayAsList) {
         Ints$IntArrayAsList that = (Ints$IntArrayAsList)object;
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
         result = 31 * result + Ints.hashCode(this.array[i]);
      }

    return result;
   }

    std::string toString() {
    std::stringstream builder = new std::stringstream(this.size() * 5);
      builder.append('[').append(this.array[this.start]);

      for (int i = this.start + 1; i < this.end; i++) {
         builder.append(", ").append(this.array[i]);
      }

      return builder.append(']');
   }

   int[] toIntArray() {
    int size = this.size();
      int[] result = new int[size];
      System.arraycopy(this.array, this.start, result, 0, size);
    return result;
   }
}
} // namespace primitives
} // namespace common
} // namespace google
} // namespace com
