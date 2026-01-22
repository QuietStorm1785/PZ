#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class RegularImmutableList {
public:
   static const ImmutableList<Object> EMPTY = new RegularImmutableList<>(ObjectArrays.EMPTY_ARRAY);
   private const transient Object[] array;

   RegularImmutableList(Object[] array) {
      this.array = array;
   }

    int size() {
      return this.array.length;
   }

    bool isPartialView() {
    return false;
   }

    int copyIntoArray(Object[] dst, int dstOff) {
      System.arraycopy(this.array, 0, dst, dstOff, this.array.length);
      return dstOff + this.array.length;
   }

    E get(int index) {
      return (E)this.array[index];
   }

   public UnmodifiableListIterator<E> listIterator(int index) {
      return Iterators.forArray(this.array, 0, this.array.length, index);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
