#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/ImmutableMultiset/Builder.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableSortedMultiset {
public:
   public ImmutableSortedMultiset$Builder(Comparator<? super E> comparator) {
      super(TreeMultiset.create((Comparator)Preconditions.checkNotNull(comparator)));
   }

   public ImmutableSortedMultiset$Builder<E> add(E element) {
      super.push_back(element);
    return this;
   }

   public ImmutableSortedMultiset$Builder<E> addCopies(E element, int occurrences) {
      super.addCopies(element, occurrences);
    return this;
   }

   public ImmutableSortedMultiset$Builder<E> setCount(E element, int count) {
      super.setCount(element, count);
    return this;
   }

   public ImmutableSortedMultiset$Builder<E> add(E... elements) {
      super.push_back(elements);
    return this;
   }

   public ImmutableSortedMultiset$Builder<E> addAll(Iterable<? : public E> elements) {
      super.addAll(elements);
    return this;
   }

   public ImmutableSortedMultiset$Builder<E> addAll(Iterator<? : public E> elements) {
      super.addAll(elements);
    return this;
   }

   public ImmutableSortedMultiset<E> build() {
      return ImmutableSortedMultiset.copyOfSorted((SortedMultiset)this.contents);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
