#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Predicate.h"
#include "com/google/common/collect/Sets/FilteredSortedSet.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Sets {
public:
   Sets$FilteredNavigableSet(NavigableSet<E> unfiltered, Predicate<? super E> predicate) {
      super(unfiltered, predicate);
   }

   NavigableSet<E> unfiltered() {
      return (NavigableSet<E>)this.unfiltered;
   }

    E lower(E e) {
      return (E)Iterators.getNext(this.headSet(e, false).descendingIterator(), nullptr);
   }

    E floor(E e) {
      return (E)Iterators.getNext(this.headSet(e, true).descendingIterator(), nullptr);
   }

    E ceiling(E e) {
      return (E)Iterables.getFirst(this.tailSet(e, true), nullptr);
   }

    E higher(E e) {
      return (E)Iterables.getFirst(this.tailSet(e, false), nullptr);
   }

    E pollFirst() {
      return (E)Iterables.removeFirstMatching(this.unfiltered(), this.predicate);
   }

    E pollLast() {
      return (E)Iterables.removeFirstMatching(this.unfiltered().descendingSet(), this.predicate);
   }

   public NavigableSet<E> descendingSet() {
      return Sets.filter(this.unfiltered().descendingSet(), this.predicate);
   }

   public Iterator<E> descendingIterator() {
      return Iterators.filter(this.unfiltered().descendingIterator(), this.predicate);
   }

    E last() {
      return this.descendingIterator().next();
   }

   public NavigableSet<E> subSet(E fromElement, boolean fromInclusive, E toElement, boolean toInclusive) {
      return Sets.filter(this.unfiltered().subSet(fromElement, fromInclusive, toElement, toInclusive), this.predicate);
   }

   public NavigableSet<E> headSet(E toElement, boolean inclusive) {
      return Sets.filter(this.unfiltered().headSet(toElement, inclusive), this.predicate);
   }

   public NavigableSet<E> tailSet(E fromElement, boolean inclusive) {
      return Sets.filter(this.unfiltered().tailSet(fromElement, inclusive), this.predicate);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
