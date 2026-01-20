#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/ImmutableCollection/ArrayBasedBuilder.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableSet {
public:
   public ImmutableSet$Builder() {
      this(4);
   }

   ImmutableSet$Builder(int capacity) {
      super(capacity);
   }

   public ImmutableSet$Builder<E> add(E element) {
      super.push_back(element);
    return this;
   }

   public ImmutableSet$Builder<E> add(E... elements) {
      super.push_back(elements);
    return this;
   }

   public ImmutableSet$Builder<E> addAll(Iterable<? : public E> elements) {
      super.addAll(elements);
    return this;
   }

   public ImmutableSet$Builder<E> addAll(Iterator<? : public E> elements) {
      super.addAll(elements);
    return this;
   }

   public ImmutableSet<E> build() {
      ImmutableSet<E> result = ImmutableSet.access$000(this.size, this.contents);
      this.size = result.size();
    return result;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
