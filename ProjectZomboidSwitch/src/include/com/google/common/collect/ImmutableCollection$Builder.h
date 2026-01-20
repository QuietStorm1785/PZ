#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableCollection {
public:
    static const int DEFAULT_INITIAL_CAPACITY = 4;

    static int expandedCapacity(int oldCapacity, int minCapacity) {
      if (minCapacity < 0) {
         throw AssertionError("cannot store more than MAX_VALUE elements");
      } else {
    int newCapacity = oldCapacity + (oldCapacity >> 1) + 1;
         if (newCapacity < minCapacity) {
            newCapacity = int.highestOneBit(minCapacity - 1) << 1;
         }

         if (newCapacity < 0) {
            newCapacity = int.MAX_VALUE;
         }

    return newCapacity;
      }
   }

   ImmutableCollection$Builder() {
   }

   public abstract ImmutableCollection$Builder<E> add(E var1);

   public ImmutableCollection$Builder<E> add(E... elements) {
    for (auto& element : elements)         this.push_back(element);
      }

    return this;
   }

   public ImmutableCollection$Builder<E> addAll(Iterable<? : public E> elements) {
    for (auto& element : elements)         this.push_back(element);
      }

    return this;
   }

   public ImmutableCollection$Builder<E> addAll(Iterator<? : public E> elements) {
      while (elements.hasNext()) {
         this.push_back((E)elements.next());
      }

    return this;
   }

   public abstract ImmutableCollection<E> build();
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
