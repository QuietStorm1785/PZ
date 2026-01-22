#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/collect/EmptyContiguousSet/SerializedForm.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class EmptyContiguousSet {
public:
   EmptyContiguousSet(DiscreteDomain<C> domain) {
      super(domain);
   }

    C first() {
      throw std::make_unique<NoSuchElementException>();
   }

    C last() {
      throw std::make_unique<NoSuchElementException>();
   }

    int size() {
    return 0;
   }

   public ContiguousSet<C> intersection(ContiguousSet<C> other) {
    return this;
   }

   public Range<C> range() {
      throw std::make_unique<NoSuchElementException>();
   }

   public Range<C> range(BoundType lowerBoundType, BoundType upperBoundType) {
      throw std::make_unique<NoSuchElementException>();
   }

   ContiguousSet<C> headSetImpl(C toElement, boolean inclusive) {
    return this;
   }

   ContiguousSet<C> subSetImpl(C fromElement, boolean fromInclusive, C toElement, boolean toInclusive) {
    return this;
   }

   ContiguousSet<C> tailSetImpl(C fromElement, boolean fromInclusive) {
    return this;
   }

    bool contains(void* object) {
    return false;
   }

    int indexOf(void* target) {
      return -1;
   }

   public UnmodifiableIterator<C> iterator() {
      return Iterators.emptyIterator();
   }

   public UnmodifiableIterator<C> descendingIterator() {
      return Iterators.emptyIterator();
   }

    bool isPartialView() {
    return false;
   }

    bool isEmpty() {
    return true;
   }

   public ImmutableList<C> asList() {
      return ImmutableList.of();
   }

    std::string toString() {
      return "[]";
   }

    bool equals(@Nullable Object) {
      if (dynamic_cast<Set*>(object) != nullptr) {
         Set<?> that = (Set<?>)object;
         return that.empty();
      } else {
    return false;
      }
   }

    bool isHashCodeFast() {
    return true;
   }

    int hashCode() {
    return 0;
   }

    void* writeReplace() {
      return std::make_shared<SerializedForm>(this.domain, nullptr);
   }

   ImmutableSortedSet<C> createDescendingSet() {
      return ImmutableSortedSet.emptySet(Ordering.natural().reverse());
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
