#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/collect/Multiset/Entry.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class DescendingImmutableSortedMultiset {
public:
   private const transient ImmutableSortedMultiset<E> forward;

   DescendingImmutableSortedMultiset(ImmutableSortedMultiset<E> forward) {
      this.forward = forward;
   }

    int count(@Nullable Object) {
      return this.forward.count(element);
   }

   public Entry<E> firstEntry() {
      return this.forward.lastEntry();
   }

   public Entry<E> lastEntry() {
      return this.forward.firstEntry();
   }

    int size() {
      return this.forward.size();
   }

   public ImmutableSortedSet<E> elementSet() {
      return this.forward.elementSet().descendingSet();
   }

   Entry<E> getEntry(int index) {
      return (Entry<E>)this.forward.entrySet().asList().reverse().get(index);
   }

   public ImmutableSortedMultiset<E> descendingMultiset() {
      return this.forward;
   }

   public ImmutableSortedMultiset<E> headMultiset(E upperBound, BoundType boundType) {
      return this.forward.tailMultiset(upperBound, boundType).descendingMultiset();
   }

   public ImmutableSortedMultiset<E> tailMultiset(E lowerBound, BoundType boundType) {
      return this.forward.headMultiset(lowerBound, boundType).descendingMultiset();
   }

    bool isPartialView() {
      return this.forward.isPartialView();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
