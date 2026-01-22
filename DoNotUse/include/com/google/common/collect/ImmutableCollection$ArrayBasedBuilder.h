#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/ImmutableCollection/Builder.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableCollection {
public:
   Object[] contents;
    int size;

   ImmutableCollection$ArrayBasedBuilder(int initialCapacity) {
      CollectPreconditions.checkNonnegative(initialCapacity, "initialCapacity");
      this.contents = new Object[initialCapacity];
      this.size = 0;
   }

    void ensureCapacity(int minCapacity) {
      if (this.contents.length < minCapacity) {
         this.contents = ObjectArrays.arraysCopyOf(this.contents, expandedCapacity(this.contents.length, minCapacity));
      }
   }

   public ImmutableCollection$ArrayBasedBuilder<E> add(E element) {
      Preconditions.checkNotNull(element);
      this.ensureCapacity(this.size + 1);
      this.contents[this.size++] = element;
    return this;
   }

   public Builder<E> add(E... elements) {
      ObjectArrays.checkElementsNotNull(elements);
      this.ensureCapacity(this.size + elements.length);
      System.arraycopy(elements, 0, this.contents, this.size, elements.length);
      this.size += elements.length;
    return this;
   }

   public Builder<E> addAll(Iterable<? : public E> elements) {
      if (dynamic_cast<Collection*>(elements) != nullptr) {
         Collection<?> collection = (Collection<?>)elements;
         this.ensureCapacity(this.size + collection.size());
      }

      super.addAll(elements);
    return this;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
