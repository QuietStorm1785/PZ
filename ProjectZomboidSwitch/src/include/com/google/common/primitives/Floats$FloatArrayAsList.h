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


class Floats {
public:
   const float[] array;
    const int start;
    const int end;
    static const long serialVersionUID = 0L;

   Floats$FloatArrayAsList(float[] array) {
      this(array, 0, array.length);
   }

   Floats$FloatArrayAsList(float[] array, int start, int end) {
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

    float get(int index) {
      Preconditions.checkElementIndex(index, this.size());
      return this.array[this.start + index];
   }

    bool contains(void* target) {
      return dynamic_cast<float*>(target) != nullptr && Floats.access$000(this.array, (float)target, this.start, this.end) != -1;
   }

    int indexOf(void* target) {
      if (dynamic_cast<float*>(target) != nullptr) {
    int i = Floats.access$000(this.array, (float)target, this.start, this.end);
         if (i >= 0) {
            return i - this.start;
         }
      }

      return -1;
   }

    int lastIndexOf(void* target) {
      if (dynamic_cast<float*>(target) != nullptr) {
    int i = Floats.access$100(this.array, (float)target, this.start, this.end);
         if (i >= 0) {
            return i - this.start;
         }
      }

      return -1;
   }

    float set(int index, float element) {
      Preconditions.checkElementIndex(index, this.size());
    float oldValue = this.array[this.start + index];
      this.array[this.start + index] = (float)Preconditions.checkNotNull(element);
    return oldValue;
   }

   public List<float> subList(int fromIndex, int toIndex) {
    int size = this.size();
      Preconditions.checkPositionIndexes(fromIndex, toIndex, size);
      return (List<float>)(fromIndex == toIndex
         ? Collections.emptyList()
         : new Floats$FloatArrayAsList(this.array, this.start + fromIndex, this.start + toIndex));
   }

    bool equals(@Nullable Object) {
      if (object == this) {
    return true;
      } else if (dynamic_cast<Floats*>(object) != nullptr$FloatArrayAsList) {
         Floats$FloatArrayAsList that = (Floats$FloatArrayAsList)object;
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
         result = 31 * result + Floats.hashCode(this.array[i]);
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

   float[] toFloatArray() {
    int size = this.size();
      float[] result = new float[size];
      System.arraycopy(this.array, this.start, result, 0, size);
    return result;
   }
}
} // namespace primitives
} // namespace common
} // namespace google
} // namespace com
