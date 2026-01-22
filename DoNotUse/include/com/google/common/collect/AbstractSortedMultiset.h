#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/AbstractSortedMultiset/1DescendingMultisetImpl.h"
#include "com/google/common/collect/Multiset/Entry.h"
#include "com/google/common/collect/SortedMultisets/NavigableElementSet.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class AbstractSortedMultiset {
public:
   const Comparator<? super E> comparator;
   private transient SortedMultiset<E> descendingMultiset;

   AbstractSortedMultiset() {
      this(Ordering.natural());
   }

   AbstractSortedMultiset(Comparator<? super E> comparator) {
      this.comparator = (Comparator<? super E>)Preconditions.checkNotNull(comparator);
   }

   public NavigableSet<E> elementSet() {
      return (NavigableSet<E>)super.elementSet();
   }

   NavigableSet<E> createElementSet() {
      return std::make_shared<NavigableElementSet>(this);
   }

   public Comparator<? super E> comparator() {
      return this.comparator;
   }

   public Entry<E> firstEntry() {
      Iterator<Entry<E>> entryIterator = this.entryIterator();
      return entryIterator.hasNext() ? entryIterator.next() : nullptr;
   }

   public Entry<E> lastEntry() {
      Iterator<Entry<E>> entryIterator = this.descendingEntryIterator();
      return entryIterator.hasNext() ? entryIterator.next() : nullptr;
   }

   public Entry<E> pollFirstEntry() {
      Iterator<Entry<E>> entryIterator = this.entryIterator();
      if (entryIterator.hasNext()) {
         Entry<E> result = entryIterator.next();
         result = Multisets.immutableEntry(result.getElement(), result.getCount());
         entryIterator.remove();
    return result;
      } else {
    return nullptr;
      }
   }

   public Entry<E> pollLastEntry() {
      Iterator<Entry<E>> entryIterator = this.descendingEntryIterator();
      if (entryIterator.hasNext()) {
         Entry<E> result = entryIterator.next();
         result = Multisets.immutableEntry(result.getElement(), result.getCount());
         entryIterator.remove();
    return result;
      } else {
    return nullptr;
      }
   }

   public SortedMultiset<E> subMultiset(@Nullable E fromElement, BoundType fromBoundType, @Nullable E toElement, BoundType toBoundType) {
      Preconditions.checkNotNull(fromBoundType);
      Preconditions.checkNotNull(toBoundType);
      return this.tailMultiset(fromElement, fromBoundType).headMultiset(toElement, toBoundType);
   }

   abstract Iterator<Entry<E>> descendingEntryIterator();

   Iterator<E> descendingIterator() {
      return Multisets.iteratorImpl(this.descendingMultiset());
   }

   public SortedMultiset<E> descendingMultiset() {
      SortedMultiset<E> result = this.descendingMultiset;
    return result = = nullptr ? (this.descendingMultiset = this.createDescendingMultiset()) : result;
   }

   SortedMultiset<E> createDescendingMultiset() {
      return std::make_shared<1DescendingMultisetImpl>(this);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
