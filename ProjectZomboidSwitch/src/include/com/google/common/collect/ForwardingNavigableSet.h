#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class ForwardingNavigableSet {
public:
    protected ForwardingNavigableSet() {
   }

   protected abstract NavigableSet<E> delegate();

    E lower(E e) {
      return this.delegate().lower(e);
   }

    E standardLower(E e) {
      return (E)Iterators.getNext(this.headSet(e, false).descendingIterator(), nullptr);
   }

    E floor(E e) {
      return this.delegate().floor(e);
   }

    E standardFloor(E e) {
      return (E)Iterators.getNext(this.headSet(e, true).descendingIterator(), nullptr);
   }

    E ceiling(E e) {
      return this.delegate().ceiling(e);
   }

    E standardCeiling(E e) {
      return (E)Iterators.getNext(this.tailSet(e, true).iterator(), nullptr);
   }

    E higher(E e) {
      return this.delegate().higher(e);
   }

    E standardHigher(E e) {
      return (E)Iterators.getNext(this.tailSet(e, false).iterator(), nullptr);
   }

    E pollFirst() {
      return this.delegate().pollFirst();
   }

    E standardPollFirst() {
      return (E)Iterators.pollNext(this.iterator());
   }

    E pollLast() {
      return this.delegate().pollLast();
   }

    E standardPollLast() {
      return (E)Iterators.pollNext(this.descendingIterator());
   }

    E standardFirst() {
      return this.iterator().next();
   }

    E standardLast() {
      return this.descendingIterator().next();
   }

   public NavigableSet<E> descendingSet() {
      return this.delegate().descendingSet();
   }

   public Iterator<E> descendingIterator() {
      return this.delegate().descendingIterator();
   }

   public NavigableSet<E> subSet(E fromElement, boolean fromInclusive, E toElement, boolean toInclusive) {
      return this.delegate().subSet(fromElement, fromInclusive, toElement, toInclusive);
   }

   protected NavigableSet<E> standardSubSet(E fromElement, boolean fromInclusive, E toElement, boolean toInclusive) {
      return this.tailSet(fromElement, fromInclusive).headSet(toElement, toInclusive);
   }

   protected SortedSet<E> standardSubSet(E fromElement, E toElement) {
      return this.subSet(fromElement, true, toElement, false);
   }

   public NavigableSet<E> headSet(E toElement, boolean inclusive) {
      return this.delegate().headSet(toElement, inclusive);
   }

   protected SortedSet<E> standardHeadSet(E toElement) {
      return this.headSet(toElement, false);
   }

   public NavigableSet<E> tailSet(E fromElement, boolean inclusive) {
      return this.delegate().tailSet(fromElement, inclusive);
   }

   protected SortedSet<E> standardTailSet(E fromElement) {
      return this.tailSet(fromElement, true);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
