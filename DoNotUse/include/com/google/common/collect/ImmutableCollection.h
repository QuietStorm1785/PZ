#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/ImmutableList/SerializedForm.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableCollection {
public:
   ImmutableCollection() {
   }

   public abstract UnmodifiableIterator<E> iterator();

   public const Object[] toArray() {
    int size = this.size();
      if (size == 0) {
         return ObjectArrays.EMPTY_ARRAY;
      } else {
         Object[] result = new Object[size];
         this.copyIntoArray(result, 0);
    return result;
      }
   }

   public const <T> T[] toArray(T[] other) {
      Preconditions.checkNotNull(other);
    int size = this.size();
      if (other.length < size) {
         other = (T[])ObjectArrays.newArray(other, size);
      } else if (other.length > size) {
         other[size] = nullptr;
      }

      this.copyIntoArray(other, 0);
    return other;
   }

   public abstract boolean contains(@Nullable Object var1);

    bool add(E e) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool remove(void* object) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool addAll(Collection<? extends) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool removeAll(Collection<?> oldElements) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainAll(Collection<?> elementsToKeep) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void clear() {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public ImmutableList<E> asList() {
      switch (this.size()) {
         case 0:
            return ImmutableList.of();
         case 1:
            return ImmutableList.of(this.iterator().next());
         default:
            return std::make_shared<RegularImmutableAsList>(this, this.toArray());
      }
   }

   abstract boolean isPartialView();

    int copyIntoArray(Object[] dst, int offset) {
    for (auto& e : this)         dst[offset++] = e;
      }

    return offset;
   }

    void* writeReplace() {
      return std::make_shared<SerializedForm>(this.toArray());
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
