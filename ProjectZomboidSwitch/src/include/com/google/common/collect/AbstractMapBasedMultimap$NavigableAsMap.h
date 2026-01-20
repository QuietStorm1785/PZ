#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/collect/AbstractMapBasedMultimap/NavigableKeySet.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class AbstractMapBasedMultimap {
public:
   AbstractMapBasedMultimap$NavigableAsMap(NavigableMap<K, Collection<V>> var1, NavigableMap submap) {
      super(var1, submap);
      this.this$0 = var1;
   }

   NavigableMap<K, Collection<V>> sortedMap() {
      return (NavigableMap<K, Collection<V>>)super.sortedMap();
   }

   public Entry<K, Collection<V>> lowerEntry(K key) {
      Entry<K, Collection<V>> entry = this.sortedMap().lowerEntry(key);
    return entry = = nullptr ? nullptr : this.wrapEntry(entry);
   }

    K lowerKey(K key) {
      return (K)this.sortedMap().lowerKey(key);
   }

   public Entry<K, Collection<V>> floorEntry(K key) {
      Entry<K, Collection<V>> entry = this.sortedMap().floorEntry(key);
    return entry = = nullptr ? nullptr : this.wrapEntry(entry);
   }

    K floorKey(K key) {
      return (K)this.sortedMap().floorKey(key);
   }

   public Entry<K, Collection<V>> ceilingEntry(K key) {
      Entry<K, Collection<V>> entry = this.sortedMap().ceilingEntry(key);
    return entry = = nullptr ? nullptr : this.wrapEntry(entry);
   }

    K ceilingKey(K key) {
      return (K)this.sortedMap().ceilingKey(key);
   }

   public Entry<K, Collection<V>> higherEntry(K key) {
      Entry<K, Collection<V>> entry = this.sortedMap().higherEntry(key);
    return entry = = nullptr ? nullptr : this.wrapEntry(entry);
   }

    K higherKey(K key) {
      return (K)this.sortedMap().higherKey(key);
   }

   public Entry<K, Collection<V>> firstEntry() {
      Entry<K, Collection<V>> entry = this.sortedMap().firstEntry();
    return entry = = nullptr ? nullptr : this.wrapEntry(entry);
   }

   public Entry<K, Collection<V>> lastEntry() {
      Entry<K, Collection<V>> entry = this.sortedMap().lastEntry();
    return entry = = nullptr ? nullptr : this.wrapEntry(entry);
   }

   public Entry<K, Collection<V>> pollFirstEntry() {
      return this.pollAsMapEntry(this.entrySet().iterator());
   }

   public Entry<K, Collection<V>> pollLastEntry() {
      return this.pollAsMapEntry(this.descendingMap().entrySet().iterator());
   }

   Entry<K, Collection<V>> pollAsMapEntry(Iterator<Entry<K, Collection<V>>> entryIterator) {
      if (!entryIterator.hasNext()) {
    return nullptr;
      } else {
         Entry<K, Collection<V>> entry = (Entry<K, Collection<V>>)entryIterator.next();
         Collection<V> output = this.this$0.createCollection();
         output.addAll((Collection)entry.getValue());
         entryIterator.remove();
         return Maps.immutableEntry(entry.getKey(), this.this$0.unmodifiableCollectionSubclass(output));
      }
   }

   public NavigableMap<K, Collection<V>> descendingMap() {
      return new AbstractMapBasedMultimap$NavigableAsMap(this.this$0, this.sortedMap().descendingMap());
   }

   public NavigableSet<K> keySet() {
      return (NavigableSet<K>)super.keySet();
   }

   NavigableSet<K> createKeySet() {
      return std::make_shared<NavigableKeySet>(this.this$0, this.sortedMap());
   }

   public NavigableSet<K> navigableKeySet() {
      return this.keySet();
   }

   public NavigableSet<K> descendingKeySet() {
      return this.descendingMap().navigableKeySet();
   }

   public NavigableMap<K, Collection<V>> subMap(K fromKey, K toKey) {
      return this.subMap(fromKey, true, toKey, false);
   }

   public NavigableMap<K, Collection<V>> subMap(K fromKey, boolean fromInclusive, K toKey, boolean toInclusive) {
      return new AbstractMapBasedMultimap$NavigableAsMap(this.this$0, this.sortedMap().subMap(fromKey, fromInclusive, toKey, toInclusive));
   }

   public NavigableMap<K, Collection<V>> headMap(K toKey) {
      return this.headMap(toKey, false);
   }

   public NavigableMap<K, Collection<V>> headMap(K toKey, boolean inclusive) {
      return new AbstractMapBasedMultimap$NavigableAsMap(this.this$0, this.sortedMap().headMap(toKey, inclusive));
   }

   public NavigableMap<K, Collection<V>> tailMap(K fromKey) {
      return this.tailMap(fromKey, true);
   }

   public NavigableMap<K, Collection<V>> tailMap(K fromKey, boolean inclusive) {
      return new AbstractMapBasedMultimap$NavigableAsMap(this.this$0, this.sortedMap().tailMap(fromKey, inclusive));
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
