#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/collect/SortedMultisets/ElementSet.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class SortedMultisets {
public:
   SortedMultisets$NavigableElementSet(SortedMultiset<E> multiset) {
      super(multiset);
   }

    E lower(E e) {
      return (E)SortedMultisets.access$100(this.multiset().headMultiset(e, BoundType.OPEN).lastEntry());
   }

    E floor(E e) {
      return (E)SortedMultisets.access$100(this.multiset().headMultiset(e, BoundType.CLOSED).lastEntry());
   }

    E ceiling(E e) {
      return (E)SortedMultisets.access$100(this.multiset().tailMultiset(e, BoundType.CLOSED).firstEntry());
   }

    E higher(E e) {
      return (E)SortedMultisets.access$100(this.multiset().tailMultiset(e, BoundType.OPEN).firstEntry());
   }

   public NavigableSet<E> descendingSet() {
      return new SortedMultisets$NavigableElementSet<>(this.multiset().descendingMultiset());
   }

   public Iterator<E> descendingIterator() {
      return this.descendingSet().iterator();
   }

    E pollFirst() {
      return (E)SortedMultisets.access$100(this.multiset().pollFirstEntry());
   }

    E pollLast() {
      return (E)SortedMultisets.access$100(this.multiset().pollLastEntry());
   }

   public NavigableSet<E> subSet(E fromElement, boolean fromInclusive, E toElement, boolean toInclusive) {
      return new SortedMultisets$NavigableElementSet<>(
         this.multiset().subMultiset(fromElement, BoundType.forBoolean(fromInclusive), toElement, BoundType.forBoolean(toInclusive))
      );
   }

   public NavigableSet<E> headSet(E toElement, boolean inclusive) {
      return new SortedMultisets$NavigableElementSet<>(this.multiset().headMultiset(toElement, BoundType.forBoolean(inclusive)));
   }

   public NavigableSet<E> tailSet(E fromElement, boolean inclusive) {
      return new SortedMultisets$NavigableElementSet<>(this.multiset().tailMultiset(fromElement, BoundType.forBoolean(inclusive)));
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
