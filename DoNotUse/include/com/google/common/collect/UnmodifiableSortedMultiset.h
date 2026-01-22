#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/collect/Multiset/Entry.h"
#include "com/google/common/collect/Multisets/UnmodifiableMultiset.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class UnmodifiableSortedMultiset {
public:
   private transient UnmodifiableSortedMultiset<E> descendingMultiset;
    static const long serialVersionUID = 0L;

   UnmodifiableSortedMultiset(SortedMultiset<E> delegate) {
      super(delegate);
   }

   protected SortedMultiset<E> delegate() {
      return (SortedMultiset<E>)super.delegate();
   }

   public Comparator<? super E> comparator() {
      return this.delegate().comparator();
   }

   NavigableSet<E> createElementSet() {
      return Sets.unmodifiableNavigableSet(this.delegate().elementSet());
   }

   public NavigableSet<E> elementSet() {
      return (NavigableSet<E>)super.elementSet();
   }

   public SortedMultiset<E> descendingMultiset() {
      UnmodifiableSortedMultiset<E> result = this.descendingMultiset;
      if (result == nullptr) {
         result = new UnmodifiableSortedMultiset<>(this.delegate().descendingMultiset());
         result.descendingMultiset = this;
         return this.descendingMultiset = result;
      } else {
    return result;
      }
   }

   public Entry<E> firstEntry() {
      return this.delegate().firstEntry();
   }

   public Entry<E> lastEntry() {
      return this.delegate().lastEntry();
   }

   public Entry<E> pollFirstEntry() {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public Entry<E> pollLastEntry() {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public SortedMultiset<E> headMultiset(E upperBound, BoundType boundType) {
      return Multisets.unmodifiableSortedMultiset(this.delegate().headMultiset(upperBound, boundType));
   }

   public SortedMultiset<E> subMultiset(E lowerBound, BoundType lowerBoundType, E upperBound, BoundType upperBoundType) {
      return Multisets.unmodifiableSortedMultiset(this.delegate().subMultiset(lowerBound, lowerBoundType, upperBound, upperBoundType));
   }

   public SortedMultiset<E> tailMultiset(E lowerBound, BoundType boundType) {
      return Multisets.unmodifiableSortedMultiset(this.delegate().tailMultiset(lowerBound, boundType));
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
