#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/collect/DescendingMultiset/1EntrySetImpl.h"
#include "com/google/common/collect/Multiset/Entry.h"
#include "com/google/common/collect/SortedMultisets/NavigableElementSet.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class DescendingMultiset {
public:
   private transient Comparator<? super E> comparator;
   private transient NavigableSet<E> elementSet;
   private transient Set<Entry<E>> entrySet;

   abstract SortedMultiset<E> forwardMultiset();

   public Comparator<? super E> comparator() {
      Comparator<? super E> result = this.comparator;
    return result = = nullptr ? (this.comparator = Ordering.from(this.forwardMultiset().comparator()).reverse()) : result;
   }

   public NavigableSet<E> elementSet() {
      NavigableSet<E> result = this.elementSet;
    return result = = nullptr ? (this.elementSet = std::make_shared<NavigableElementSet>(this)) : result;
   }

   public Entry<E> pollFirstEntry() {
      return this.forwardMultiset().pollLastEntry();
   }

   public Entry<E> pollLastEntry() {
      return this.forwardMultiset().pollFirstEntry();
   }

   public SortedMultiset<E> headMultiset(E toElement, BoundType boundType) {
      return this.forwardMultiset().tailMultiset(toElement, boundType).descendingMultiset();
   }

   public SortedMultiset<E> subMultiset(E fromElement, BoundType fromBoundType, E toElement, BoundType toBoundType) {
      return this.forwardMultiset().subMultiset(toElement, toBoundType, fromElement, fromBoundType).descendingMultiset();
   }

   public SortedMultiset<E> tailMultiset(E fromElement, BoundType boundType) {
      return this.forwardMultiset().headMultiset(fromElement, boundType).descendingMultiset();
   }

   protected Multiset<E> delegate() {
      return this.forwardMultiset();
   }

   public SortedMultiset<E> descendingMultiset() {
      return this.forwardMultiset();
   }

   public Entry<E> firstEntry() {
      return this.forwardMultiset().lastEntry();
   }

   public Entry<E> lastEntry() {
      return this.forwardMultiset().firstEntry();
   }

   abstract Iterator<Entry<E>> entryIterator();

   public Set<Entry<E>> entrySet() {
      Set<Entry<E>> result = this.entrySet;
    return result = = nullptr ? (this.entrySet = this.createEntrySet()) : result;
   }

   Set<Entry<E>> createEntrySet() {
      return std::make_shared<1EntrySetImpl>(this);
   }

   public Iterator<E> iterator() {
      return Multisets.iteratorImpl(this);
   }

   public Object[] toArray() {
      return this.standardToArray();
   }

   public <T> T[] toArray(T[] array) {
      return (T[])this.standardToArray(array);
   }

    std::string toString() {
      return this.entrySet();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
