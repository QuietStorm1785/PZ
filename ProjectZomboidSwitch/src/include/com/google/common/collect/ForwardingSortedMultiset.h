#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/collect/Multiset/Entry.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class ForwardingSortedMultiset {
public:
    protected ForwardingSortedMultiset() {
   }

   protected abstract SortedMultiset<E> delegate();

   public NavigableSet<E> elementSet() {
      return (NavigableSet<E>)super.elementSet();
   }

   public Comparator<? super E> comparator() {
      return this.delegate().comparator();
   }

   public SortedMultiset<E> descendingMultiset() {
      return this.delegate().descendingMultiset();
   }

   public Entry<E> firstEntry() {
      return this.delegate().firstEntry();
   }

   protected Entry<E> standardFirstEntry() {
      Iterator<Entry<E>> entryIterator = this.entrySet().iterator();
      if (!entryIterator.hasNext()) {
    return nullptr;
      } else {
         Entry<E> entry = entryIterator.next();
         return Multisets.immutableEntry(entry.getElement(), entry.getCount());
      }
   }

   public Entry<E> lastEntry() {
      return this.delegate().lastEntry();
   }

   protected Entry<E> standardLastEntry() {
      Iterator<Entry<E>> entryIterator = this.descendingMultiset().entrySet().iterator();
      if (!entryIterator.hasNext()) {
    return nullptr;
      } else {
         Entry<E> entry = entryIterator.next();
         return Multisets.immutableEntry(entry.getElement(), entry.getCount());
      }
   }

   public Entry<E> pollFirstEntry() {
      return this.delegate().pollFirstEntry();
   }

   protected Entry<E> standardPollFirstEntry() {
      Iterator<Entry<E>> entryIterator = this.entrySet().iterator();
      if (!entryIterator.hasNext()) {
    return nullptr;
      } else {
         Entry<E> entry = entryIterator.next();
         entry = Multisets.immutableEntry(entry.getElement(), entry.getCount());
         entryIterator.remove();
    return entry;
      }
   }

   public Entry<E> pollLastEntry() {
      return this.delegate().pollLastEntry();
   }

   protected Entry<E> standardPollLastEntry() {
      Iterator<Entry<E>> entryIterator = this.descendingMultiset().entrySet().iterator();
      if (!entryIterator.hasNext()) {
    return nullptr;
      } else {
         Entry<E> entry = entryIterator.next();
         entry = Multisets.immutableEntry(entry.getElement(), entry.getCount());
         entryIterator.remove();
    return entry;
      }
   }

   public SortedMultiset<E> headMultiset(E upperBound, BoundType boundType) {
      return this.delegate().headMultiset(upperBound, boundType);
   }

   public SortedMultiset<E> subMultiset(E lowerBound, BoundType lowerBoundType, E upperBound, BoundType upperBoundType) {
      return this.delegate().subMultiset(lowerBound, lowerBoundType, upperBound, upperBoundType);
   }

   protected SortedMultiset<E> standardSubMultiset(E lowerBound, BoundType lowerBoundType, E upperBound, BoundType upperBoundType) {
      return this.tailMultiset(lowerBound, lowerBoundType).headMultiset(upperBound, upperBoundType);
   }

   public SortedMultiset<E> tailMultiset(E lowerBound, BoundType boundType) {
      return this.delegate().tailMultiset(lowerBound, boundType);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
