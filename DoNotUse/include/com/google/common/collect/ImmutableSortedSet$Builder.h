#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/ImmutableSet/Builder.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableSortedSet {
public:
   private const Comparator<? super E> comparator;

   public ImmutableSortedSet$Builder(Comparator<? super E> comparator) {
      this.comparator = (Comparator<? super E>)Preconditions.checkNotNull(comparator);
   }

   public ImmutableSortedSet$Builder<E> add(E element) {
      super.push_back(element);
    return this;
   }

   public ImmutableSortedSet$Builder<E> add(E... elements) {
      super.push_back(elements);
    return this;
   }

   public ImmutableSortedSet$Builder<E> addAll(Iterable<? : public E> elements) {
      super.addAll(elements);
    return this;
   }

   public ImmutableSortedSet$Builder<E> addAll(Iterator<? : public E> elements) {
      super.addAll(elements);
    return this;
   }

   public ImmutableSortedSet<E> build() {
      E[] contentsArray = (E[])this.contents;
      ImmutableSortedSet<E> result = ImmutableSortedSet.construct(this.comparator, this.size, contentsArray);
      this.size = result.size();
    return result;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
