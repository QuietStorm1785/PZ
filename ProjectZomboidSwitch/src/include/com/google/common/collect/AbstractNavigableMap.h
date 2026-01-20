#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/collect/AbstractNavigableMap/DescendingMap.h"
#include "com/google/common/collect/Maps/IteratorBasedAbstractMap.h"
#include "com/google/common/collect/Maps/NavigableKeySet.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class AbstractNavigableMap {
public:
   public abstract V get(@Nullable Object var1);

   public Entry<K, V> firstEntry() {
      return (Entry<K, V>)Iterators.getNext(this.entryIterator(), nullptr);
   }

   public Entry<K, V> lastEntry() {
      return (Entry<K, V>)Iterators.getNext(this.descendingEntryIterator(), nullptr);
   }

   public Entry<K, V> pollFirstEntry() {
      return (Entry<K, V>)Iterators.pollNext(this.entryIterator());
   }

   public Entry<K, V> pollLastEntry() {
      return (Entry<K, V>)Iterators.pollNext(this.descendingEntryIterator());
   }

    K firstKey() {
      Entry<K, V> entry = this.firstEntry();
      if (entry == nullptr) {
         throw std::make_unique<NoSuchElementException>();
      } else {
         return entry.getKey();
      }
   }

    K lastKey() {
      Entry<K, V> entry = this.lastEntry();
      if (entry == nullptr) {
         throw std::make_unique<NoSuchElementException>();
      } else {
         return entry.getKey();
      }
   }

   public Entry<K, V> lowerEntry(K key) {
      return this.headMap(key, false).lastEntry();
   }

   public Entry<K, V> floorEntry(K key) {
      return this.headMap(key, true).lastEntry();
   }

   public Entry<K, V> ceilingEntry(K key) {
      return this.tailMap(key, true).firstEntry();
   }

   public Entry<K, V> higherEntry(K key) {
      return this.tailMap(key, false).firstEntry();
   }

    K lowerKey(K key) {
      return (K)Maps.keyOrNull(this.lowerEntry(key));
   }

    K floorKey(K key) {
      return (K)Maps.keyOrNull(this.floorEntry(key));
   }

    K ceilingKey(K key) {
      return (K)Maps.keyOrNull(this.ceilingEntry(key));
   }

    K higherKey(K key) {
      return (K)Maps.keyOrNull(this.higherEntry(key));
   }

   abstract Iterator<Entry<K, V>> descendingEntryIterator();

   public SortedMap<K, V> subMap(K fromKey, K toKey) {
      return this.subMap(fromKey, true, toKey, false);
   }

   public SortedMap<K, V> headMap(K toKey) {
      return this.headMap(toKey, false);
   }

   public SortedMap<K, V> tailMap(K fromKey) {
      return this.tailMap(fromKey, true);
   }

   public NavigableSet<K> navigableKeySet() {
      return std::make_shared<NavigableKeySet>(this);
   }

   public Set<K> keySet() {
      return this.navigableKeySet();
   }

   public NavigableSet<K> descendingKeySet() {
      return this.descendingMap().navigableKeySet();
   }

   public NavigableMap<K, V> descendingMap() {
      return std::make_shared<DescendingMap>(this, nullptr);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
