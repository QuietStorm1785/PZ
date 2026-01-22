#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class DescendingImmutableSortedSet {
public:
   private const ImmutableSortedSet<E> forward;

   DescendingImmutableSortedSet(ImmutableSortedSet<E> forward) {
      super(Ordering.from(forward.comparator()).reverse());
      this.forward = forward;
   }

    bool contains(@Nullable Object) {
      return this.forward.contains(object);
   }

    int size() {
      return this.forward.size();
   }

   public UnmodifiableIterator<E> iterator() {
      return this.forward.descendingIterator();
   }

   ImmutableSortedSet<E> headSetImpl(E toElement, boolean inclusive) {
      return this.forward.tailSet(toElement, inclusive).descendingSet();
   }

   ImmutableSortedSet<E> subSetImpl(E fromElement, boolean fromInclusive, E toElement, boolean toInclusive) {
      return this.forward.subSet(toElement, toInclusive, fromElement, fromInclusive).descendingSet();
   }

   ImmutableSortedSet<E> tailSetImpl(E fromElement, boolean inclusive) {
      return this.forward.headSet(fromElement, inclusive).descendingSet();
   }

   public ImmutableSortedSet<E> descendingSet() {
      return this.forward;
   }

   public UnmodifiableIterator<E> descendingIterator() {
      return this.forward.iterator();
   }

   ImmutableSortedSet<E> createDescendingSet() {
      throw AssertionError("should never be called");
   }

    E lower(E element) {
      return (E)this.forward.higher(element);
   }

    E floor(E element) {
      return (E)this.forward.ceiling(element);
   }

    E ceiling(E element) {
      return (E)this.forward.floor(element);
   }

    E higher(E element) {
      return (E)this.forward.lower(element);
   }

    int indexOf(@Nullable Object) {
    int index = this.forward.indexOf(target);
    return index = = -1 ? index : this.size() - 1 - index;
   }

    bool isPartialView() {
      return this.forward.isPartialView();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
