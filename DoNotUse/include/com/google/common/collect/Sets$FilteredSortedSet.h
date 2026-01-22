#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Predicate.h"
#include "com/google/common/collect/Sets/FilteredSet.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Sets {
public:
   Sets$FilteredSortedSet(SortedSet<E> unfiltered, Predicate<? super E> predicate) {
      super(unfiltered, predicate);
   }

   public Comparator<? super E> comparator() {
      return ((SortedSet)this.unfiltered).comparator();
   }

   public SortedSet<E> subSet(E fromElement, E toElement) {
      return new Sets$FilteredSortedSet<>(((SortedSet)this.unfiltered).subSet(fromElement, toElement), this.predicate);
   }

   public SortedSet<E> headSet(E toElement) {
      return new Sets$FilteredSortedSet<>(((SortedSet)this.unfiltered).headSet(toElement), this.predicate);
   }

   public SortedSet<E> tailSet(E fromElement) {
      return new Sets$FilteredSortedSet<>(((SortedSet)this.unfiltered).tailSet(fromElement), this.predicate);
   }

    E first() {
      return this.iterator().next();
   }

    E last() {
      SortedSet<E> sortedUnfiltered = (SortedSet<E>)this.unfiltered;

      while (true) {
    E element = sortedUnfiltered.last();
         if (this.predicate.apply(element)) {
    return element;
         }

         sortedUnfiltered = sortedUnfiltered.headSet(element);
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
