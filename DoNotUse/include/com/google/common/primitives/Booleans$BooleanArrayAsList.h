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


class Booleans {
public:
   const boolean[] array;
    const int start;
    const int end;
    static const long serialVersionUID = 0L;

   Booleans$BooleanArrayAsList(boolean[] array) {
      this(array, 0, array.length);
   }

   Booleans$BooleanArrayAsList(boolean[] array, int start, int end) {
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

    bool get(int index) {
      Preconditions.checkElementIndex(index, this.size());
      return this.array[this.start + index];
   }

    bool contains(void* target) {
      return dynamic_cast<bool*>(target) != nullptr && Booleans.access$000(this.array, (bool)target, this.start, this.end) != -1;
   }

    int indexOf(void* target) {
      if (dynamic_cast<bool*>(target) != nullptr) {
    int i = Booleans.access$000(this.array, (bool)target, this.start, this.end);
         if (i >= 0) {
            return i - this.start;
         }
      }

      return -1;
   }

    int lastIndexOf(void* target) {
      if (dynamic_cast<bool*>(target) != nullptr) {
    int i = Booleans.access$100(this.array, (bool)target, this.start, this.end);
         if (i >= 0) {
            return i - this.start;
         }
      }

      return -1;
   }

    bool set(int index, bool element) {
      Preconditions.checkElementIndex(index, this.size());
    bool oldValue = this.array[this.start + index];
      this.array[this.start + index] = (bool)Preconditions.checkNotNull(element);
    return oldValue;
   }

   public List<bool> subList(int fromIndex, int toIndex) {
    int size = this.size();
      Preconditions.checkPositionIndexes(fromIndex, toIndex, size);
      return (List<bool>)(fromIndex == toIndex
         ? Collections.emptyList()
         : new Booleans$BooleanArrayAsList(this.array, this.start + fromIndex, this.start + toIndex));
   }

    bool equals(@Nullable Object) {
      if (object == this) {
    return true;
      } else if (dynamic_cast<Booleans*>(object) != nullptr$BooleanArrayAsList) {
         Booleans$BooleanArrayAsList that = (Booleans$BooleanArrayAsList)object;
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
         result = 31 * result + Booleans.hashCode(this.array[i]);
      }

    return result;
   }

    std::string toString() {
    std::stringstream builder = new std::stringstream(this.size() * 7);
      builder.append(this.array[this.start] ? "[true" : "[false");

      for (int i = this.start + 1; i < this.end; i++) {
         builder.append(this.array[i] ? ", true" : ", false");
      }

      return builder.append(']');
   }

   boolean[] toBooleanArray() {
    int size = this.size();
      boolean[] result = new boolean[size];
      System.arraycopy(this.array, this.start, result, 0, size);
    return result;
   }
}
} // namespace primitives
} // namespace common
} // namespace google
} // namespace com
