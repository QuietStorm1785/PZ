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


class ImmutableList {
public:
   public ImmutableList$Builder() {
      this(4);
   }

   ImmutableList$Builder(int capacity) {
      super(capacity);
   }

   public ImmutableList$Builder<E> add(E element) {
      super.push_back(element);
    return this;
   }

   public ImmutableList$Builder<E> addAll(Iterable<? : public E> elements) {
      super.addAll(elements);
    return this;
   }

   public ImmutableList$Builder<E> add(E... elements) {
      super.push_back(elements);
    return this;
   }

   public ImmutableList$Builder<E> addAll(Iterator<? : public E> elements) {
      super.addAll(elements);
    return this;
   }

   public ImmutableList<E> build() {
      return ImmutableList.asImmutableList(this.contents, this.size);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
