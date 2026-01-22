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


class AbstractMapBasedMultimap {
public:
   AbstractMapBasedMultimap$NavigableKeySet(NavigableMap<K, Collection<V>> var1, NavigableMap subMap) {
      super(var1, subMap);
      this.this$0 = var1;
   }

   NavigableMap<K, Collection<V>> sortedMap() {
      return (NavigableMap<K, Collection<V>>)super.sortedMap();
   }

    K lower(K k) {
      return (K)this.sortedMap().lowerKey(k);
   }

    K floor(K k) {
      return (K)this.sortedMap().floorKey(k);
   }

    K ceiling(K k) {
      return (K)this.sortedMap().ceilingKey(k);
   }

    K higher(K k) {
      return (K)this.sortedMap().higherKey(k);
   }

    K pollFirst() {
      return (K)Iterators.pollNext(this.iterator());
   }

    K pollLast() {
      return (K)Iterators.pollNext(this.descendingIterator());
   }

   public NavigableSet<K> descendingSet() {
      return new AbstractMapBasedMultimap$NavigableKeySet(this.this$0, this.sortedMap().descendingMap());
   }

   public Iterator<K> descendingIterator() {
      return this.descendingSet().iterator();
   }

   public NavigableSet<K> headSet(K toElement) {
      return this.headSet(toElement, false);
   }

   public NavigableSet<K> headSet(K toElement, boolean inclusive) {
      return new AbstractMapBasedMultimap$NavigableKeySet(this.this$0, this.sortedMap().headMap(toElement, inclusive));
   }

   public NavigableSet<K> subSet(K fromElement, K toElement) {
      return this.subSet(fromElement, true, toElement, false);
   }

   public NavigableSet<K> subSet(K fromElement, boolean fromInclusive, K toElement, boolean toInclusive) {
      return new AbstractMapBasedMultimap$NavigableKeySet(this.this$0, this.sortedMap().subMap(fromElement, fromInclusive, toElement, toInclusive));
   }

   public NavigableSet<K> tailSet(K fromElement) {
      return this.tailSet(fromElement, true);
   }

   public NavigableSet<K> tailSet(K fromElement, boolean inclusive) {
      return new AbstractMapBasedMultimap$NavigableKeySet(this.this$0, this.sortedMap().tailMap(fromElement, inclusive));
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
