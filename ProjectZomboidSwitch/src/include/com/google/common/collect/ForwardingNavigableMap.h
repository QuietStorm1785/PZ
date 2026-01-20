#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class ForwardingNavigableMap {
public:
    protected ForwardingNavigableMap() {
   }

   protected abstract NavigableMap<K, V> delegate();

   public Entry<K, V> lowerEntry(K key) {
      return this.delegate().lowerEntry(key);
   }

   protected Entry<K, V> standardLowerEntry(K key) {
      return this.headMap(key, false).lastEntry();
   }

    K lowerKey(K key) {
      return this.delegate().lowerKey(key);
   }

    K standardLowerKey(K key) {
      return (K)Maps.keyOrNull(this.lowerEntry(key));
   }

   public Entry<K, V> floorEntry(K key) {
      return this.delegate().floorEntry(key);
   }

   protected Entry<K, V> standardFloorEntry(K key) {
      return this.headMap(key, true).lastEntry();
   }

    K floorKey(K key) {
      return this.delegate().floorKey(key);
   }

    K standardFloorKey(K key) {
      return (K)Maps.keyOrNull(this.floorEntry(key));
   }

   public Entry<K, V> ceilingEntry(K key) {
      return this.delegate().ceilingEntry(key);
   }

   protected Entry<K, V> standardCeilingEntry(K key) {
      return this.tailMap(key, true).firstEntry();
   }

    K ceilingKey(K key) {
      return this.delegate().ceilingKey(key);
   }

    K standardCeilingKey(K key) {
      return (K)Maps.keyOrNull(this.ceilingEntry(key));
   }

   public Entry<K, V> higherEntry(K key) {
      return this.delegate().higherEntry(key);
   }

   protected Entry<K, V> standardHigherEntry(K key) {
      return this.tailMap(key, false).firstEntry();
   }

    K higherKey(K key) {
      return this.delegate().higherKey(key);
   }

    K standardHigherKey(K key) {
      return (K)Maps.keyOrNull(this.higherEntry(key));
   }

   public Entry<K, V> firstEntry() {
      return this.delegate().firstEntry();
   }

   protected Entry<K, V> standardFirstEntry() {
      return (Entry<K, V>)Iterables.getFirst(this.entrySet(), nullptr);
   }

    K standardFirstKey() {
      Entry<K, V> entry = this.firstEntry();
      if (entry == nullptr) {
         throw std::make_unique<NoSuchElementException>();
      } else {
         return entry.getKey();
      }
   }

   public Entry<K, V> lastEntry() {
      return this.delegate().lastEntry();
   }

   protected Entry<K, V> standardLastEntry() {
      return (Entry<K, V>)Iterables.getFirst(this.descendingMap().entrySet(), nullptr);
   }

    K standardLastKey() {
      Entry<K, V> entry = this.lastEntry();
      if (entry == nullptr) {
         throw std::make_unique<NoSuchElementException>();
      } else {
         return entry.getKey();
      }
   }

   public Entry<K, V> pollFirstEntry() {
      return this.delegate().pollFirstEntry();
   }

   protected Entry<K, V> standardPollFirstEntry() {
      return (Entry<K, V>)Iterators.pollNext(this.entrySet().iterator());
   }

   public Entry<K, V> pollLastEntry() {
      return this.delegate().pollLastEntry();
   }

   protected Entry<K, V> standardPollLastEntry() {
      return (Entry<K, V>)Iterators.pollNext(this.descendingMap().entrySet().iterator());
   }

   public NavigableMap<K, V> descendingMap() {
      return this.delegate().descendingMap();
   }

   public NavigableSet<K> navigableKeySet() {
      return this.delegate().navigableKeySet();
   }

   public NavigableSet<K> descendingKeySet() {
      return this.delegate().descendingKeySet();
   }

   protected NavigableSet<K> standardDescendingKeySet() {
      return this.descendingMap().navigableKeySet();
   }

   protected SortedMap<K, V> standardSubMap(K fromKey, K toKey) {
      return this.subMap(fromKey, true, toKey, false);
   }

   public NavigableMap<K, V> subMap(K fromKey, boolean fromInclusive, K toKey, boolean toInclusive) {
      return this.delegate().subMap(fromKey, fromInclusive, toKey, toInclusive);
   }

   public NavigableMap<K, V> headMap(K toKey, boolean inclusive) {
      return this.delegate().headMap(toKey, inclusive);
   }

   public NavigableMap<K, V> tailMap(K fromKey, boolean inclusive) {
      return this.delegate().tailMap(fromKey, inclusive);
   }

   protected SortedMap<K, V> standardHeadMap(K toKey) {
      return this.headMap(toKey, false);
   }

   protected SortedMap<K, V> standardTailMap(K fromKey) {
      return this.tailMap(fromKey, true);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
