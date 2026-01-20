#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Preconditions.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Sets {
public:
   private const NavigableSet<E> delegate;
   private transient Sets$UnmodifiableNavigableSet<E> descendingSet;
    static const long serialVersionUID = 0L;

   Sets$UnmodifiableNavigableSet(NavigableSet<E> delegate) {
      this.delegate = (NavigableSet<E>)Preconditions.checkNotNull(delegate);
   }

   protected SortedSet<E> delegate() {
      return Collections.unmodifiableSortedSet(this.delegate);
   }

    E lower(E e) {
      return this.delegate.lower(e);
   }

    E floor(E e) {
      return this.delegate.floor(e);
   }

    E ceiling(E e) {
      return this.delegate.ceiling(e);
   }

    E higher(E e) {
      return this.delegate.higher(e);
   }

    E pollFirst() {
      throw std::make_unique<UnsupportedOperationException>();
   }

    E pollLast() {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public NavigableSet<E> descendingSet() {
      Sets$UnmodifiableNavigableSet<E> result = this.descendingSet;
      if (result == nullptr) {
         result = this.descendingSet = new Sets$UnmodifiableNavigableSet<>(this.delegate.descendingSet());
         result.descendingSet = this;
      }

    return result;
   }

   public Iterator<E> descendingIterator() {
      return Iterators.unmodifiableIterator(this.delegate.descendingIterator());
   }

   public NavigableSet<E> subSet(E fromElement, boolean fromInclusive, E toElement, boolean toInclusive) {
      return Sets.unmodifiableNavigableSet(this.delegate.subSet(fromElement, fromInclusive, toElement, toInclusive));
   }

   public NavigableSet<E> headSet(E toElement, boolean inclusive) {
      return Sets.unmodifiableNavigableSet(this.delegate.headSet(toElement, inclusive));
   }

   public NavigableSet<E> tailSet(E fromElement, boolean inclusive) {
      return Sets.unmodifiableNavigableSet(this.delegate.tailSet(fromElement, inclusive));
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
