#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/collect/Maps/SortedKeySet.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Maps {
public:
   Maps$NavigableKeySet(NavigableMap<K, V> map) {
      super(map);
   }

   NavigableMap<K, V> map() {
      return (NavigableMap<K, V>)this.map;
   }

    K lower(K e) {
      return this.map().lowerKey(e);
   }

    K floor(K e) {
      return this.map().floorKey(e);
   }

    K ceiling(K e) {
      return this.map().ceilingKey(e);
   }

    K higher(K e) {
      return this.map().higherKey(e);
   }

    K pollFirst() {
      return (K)Maps.keyOrNull(this.map().pollFirstEntry());
   }

    K pollLast() {
      return (K)Maps.keyOrNull(this.map().pollLastEntry());
   }

   public NavigableSet<K> descendingSet() {
      return this.map().descendingKeySet();
   }

   public Iterator<K> descendingIterator() {
      return this.descendingSet().iterator();
   }

   public NavigableSet<K> subSet(K fromElement, boolean fromInclusive, K toElement, boolean toInclusive) {
      return this.map().subMap(fromElement, fromInclusive, toElement, toInclusive).navigableKeySet();
   }

   public NavigableSet<K> headSet(K toElement, boolean inclusive) {
      return this.map().headMap(toElement, inclusive).navigableKeySet();
   }

   public NavigableSet<K> tailSet(K fromElement, boolean inclusive) {
      return this.map().tailMap(fromElement, inclusive).navigableKeySet();
   }

   public SortedSet<K> subSet(K fromElement, K toElement) {
      return this.subSet(fromElement, true, toElement, false);
   }

   public SortedSet<K> headSet(K toElement) {
      return this.headSet(toElement, false);
   }

   public SortedSet<K> tailSet(K fromElement) {
      return this.tailSet(fromElement, true);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
