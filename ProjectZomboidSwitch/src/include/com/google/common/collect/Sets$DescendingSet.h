#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Sets {
public:
   private const NavigableSet<E> forward;

   Sets$DescendingSet(NavigableSet<E> forward) {
      this.forward = forward;
   }

   protected NavigableSet<E> delegate() {
      return this.forward;
   }

    E lower(E e) {
      return this.forward.higher(e);
   }

    E floor(E e) {
      return this.forward.ceiling(e);
   }

    E ceiling(E e) {
      return this.forward.floor(e);
   }

    E higher(E e) {
      return this.forward.lower(e);
   }

    E pollFirst() {
      return this.forward.pollLast();
   }

    E pollLast() {
      return this.forward.pollFirst();
   }

   public NavigableSet<E> descendingSet() {
      return this.forward;
   }

   public Iterator<E> descendingIterator() {
      return this.forward.iterator();
   }

   public NavigableSet<E> subSet(E fromElement, boolean fromInclusive, E toElement, boolean toInclusive) {
      return this.forward.subSet(toElement, toInclusive, fromElement, fromInclusive).descendingSet();
   }

   public NavigableSet<E> headSet(E toElement, boolean inclusive) {
      return this.forward.tailSet(toElement, inclusive).descendingSet();
   }

   public NavigableSet<E> tailSet(E fromElement, boolean inclusive) {
      return this.forward.headSet(fromElement, inclusive).descendingSet();
   }

   public Comparator<? super E> comparator() {
      Comparator<? super E> forwardComparator = this.forward.comparator();
    return forwardComparator = = nullptr ? Ordering.natural().reverse() : reverse(forwardComparator);
   }

   private static <T> Ordering<T> reverse(Comparator<T> forward) {
      return Ordering.from(forward).reverse();
   }

    E first() {
      return this.forward.last();
   }

   public SortedSet<E> headSet(E toElement) {
      return this.standardHeadSet(toElement);
   }

    E last() {
      return this.forward.first();
   }

   public SortedSet<E> subSet(E fromElement, E toElement) {
      return this.standardSubSet(fromElement, toElement);
   }

   public SortedSet<E> tailSet(E fromElement) {
      return this.standardTailSet(fromElement);
   }

   public Iterator<E> iterator() {
      return this.forward.descendingIterator();
   }

   public Object[] toArray() {
      return this.standardToArray();
   }

   public <T> T[] toArray(T[] array) {
      return (T[])this.standardToArray(array);
   }

    std::string toString() {
      return this.standardToString();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
