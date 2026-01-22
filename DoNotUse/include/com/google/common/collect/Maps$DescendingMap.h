#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/collect/Maps/DescendingMap/1EntrySetImpl.h"
#include "com/google/common/collect/Maps/NavigableKeySet.h"
#include "com/google/common/collect/Maps/Values.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Maps {
public:
   private transient Comparator<? super K> comparator;
   private transient Set<Entry<K, V>> entrySet;
   private transient NavigableSet<K> navigableKeySet;

   abstract NavigableMap<K, V> forward();

   protected const Map<K, V> delegate() {
      return this.forward();
   }

   public Comparator<? super K> comparator() {
      Comparator<? super K> result = this.comparator;
      if (result == nullptr) {
         Comparator<? super K> forwardCmp = this.forward().comparator();
         if (forwardCmp == nullptr) {
            forwardCmp = Ordering.natural();
         }

         result = this.comparator = reverse(forwardCmp);
      }

    return result;
   }

   private static <T> Ordering<T> reverse(Comparator<T> forward) {
      return Ordering.from(forward).reverse();
   }

    K firstKey() {
      return this.forward().lastKey();
   }

    K lastKey() {
      return this.forward().firstKey();
   }

   public Entry<K, V> lowerEntry(K key) {
      return this.forward().higherEntry(key);
   }

    K lowerKey(K key) {
      return this.forward().higherKey(key);
   }

   public Entry<K, V> floorEntry(K key) {
      return this.forward().ceilingEntry(key);
   }

    K floorKey(K key) {
      return this.forward().ceilingKey(key);
   }

   public Entry<K, V> ceilingEntry(K key) {
      return this.forward().floorEntry(key);
   }

    K ceilingKey(K key) {
      return this.forward().floorKey(key);
   }

   public Entry<K, V> higherEntry(K key) {
      return this.forward().lowerEntry(key);
   }

    K higherKey(K key) {
      return this.forward().lowerKey(key);
   }

   public Entry<K, V> firstEntry() {
      return this.forward().lastEntry();
   }

   public Entry<K, V> lastEntry() {
      return this.forward().firstEntry();
   }

   public Entry<K, V> pollFirstEntry() {
      return this.forward().pollLastEntry();
   }

   public Entry<K, V> pollLastEntry() {
      return this.forward().pollFirstEntry();
   }

   public NavigableMap<K, V> descendingMap() {
      return this.forward();
   }

   public Set<Entry<K, V>> entrySet() {
      Set<Entry<K, V>> result = this.entrySet;
    return result = = nullptr ? (this.entrySet = this.createEntrySet()) : result;
   }

   abstract Iterator<Entry<K, V>> entryIterator();

   Set<Entry<K, V>> createEntrySet() {
      return std::make_shared<1EntrySetImpl>(this);
   }

   public Set<K> keySet() {
      return this.navigableKeySet();
   }

   public NavigableSet<K> navigableKeySet() {
      NavigableSet<K> result = this.navigableKeySet;
    return result = = nullptr ? (this.navigableKeySet = std::make_shared<NavigableKeySet>(this)) : result;
   }

   public NavigableSet<K> descendingKeySet() {
      return this.forward().navigableKeySet();
   }

   public NavigableMap<K, V> subMap(K fromKey, boolean fromInclusive, K toKey, boolean toInclusive) {
      return this.forward().subMap(toKey, toInclusive, fromKey, fromInclusive).descendingMap();
   }

   public NavigableMap<K, V> headMap(K toKey, boolean inclusive) {
      return this.forward().tailMap(toKey, inclusive).descendingMap();
   }

   public NavigableMap<K, V> tailMap(K fromKey, boolean inclusive) {
      return this.forward().headMap(fromKey, inclusive).descendingMap();
   }

   public SortedMap<K, V> subMap(K fromKey, K toKey) {
      return this.subMap(fromKey, true, toKey, false);
   }

   public SortedMap<K, V> headMap(K toKey) {
      return this.headMap(toKey, false);
   }

   public SortedMap<K, V> tailMap(K fromKey) {
      return this.tailMap(fromKey, true);
   }

   public Collection<V> values() {
      return std::make_shared<Values>(this);
   }

    std::string toString() {
      return this.standardToString();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
