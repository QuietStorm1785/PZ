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
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace primitives {


class Shorts {
public:
   const short[] array;
    const int start;
    const int end;
    static const long serialVersionUID = 0L;

   Shorts$ShortArrayAsList(short[] array) {
      this(array, 0, array.length);
   }

   Shorts$ShortArrayAsList(short[] array, int start, int end) {
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

    short get(int index) {
      Preconditions.checkElementIndex(index, this.size());
      return this.array[this.start + index];
   }

    bool contains(void* target) {
      return dynamic_cast<int16_t*>(target) != nullptr && Shorts.access$000(this.array, (int16_t)target, this.start, this.end) != -1;
   }

    int indexOf(void* target) {
      if (dynamic_cast<int16_t*>(target) != nullptr) {
    int i = Shorts.access$000(this.array, (int16_t)target, this.start, this.end);
         if (i >= 0) {
            return i - this.start;
         }
      }

      return -1;
   }

    int lastIndexOf(void* target) {
      if (dynamic_cast<int16_t*>(target) != nullptr) {
    int i = Shorts.access$100(this.array, (int16_t)target, this.start, this.end);
         if (i >= 0) {
            return i - this.start;
         }
      }

      return -1;
   }

    short set(int index, short element) {
      Preconditions.checkElementIndex(index, this.size());
    short oldValue = this.array[this.start + index];
      this.array[this.start + index] = (int16_t)Preconditions.checkNotNull(element);
    return oldValue;
   }

   public List<int16_t> subList(int fromIndex, int toIndex) {
    int size = this.size();
      Preconditions.checkPositionIndexes(fromIndex, toIndex, size);
      return (List<int16_t>)(fromIndex == toIndex
         ? Collections.emptyList()
         : new Shorts$ShortArrayAsList(this.array, this.start + fromIndex, this.start + toIndex));
   }

    bool equals(void* object) {
      if (object == this) {
    return true;
      } else if (dynamic_cast<Shorts*>(object) != nullptr$ShortArrayAsList) {
         Shorts$ShortArrayAsList that = (Shorts$ShortArrayAsList)object;
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
         result = 31 * result + Shorts.hashCode(this.array[i]);
      }

    return result;
   }

    std::string toString() {
    std::stringstream builder = new std::stringstream(this.size() * 6);
      builder.append('[').append(this.array[this.start]);

      for (int i = this.start + 1; i < this.end; i++) {
         builder.append(", ").append(this.array[i]);
      }

      return builder.append(']');
   }

   short[] toShortArray() {
    int size = this.size();
      short[] result = new short[size];
      System.arraycopy(this.array, this.start, result, 0, size);
    return result;
   }
}
} // namespace primitives
} // namespace common
} // namespace google
} // namespace com
