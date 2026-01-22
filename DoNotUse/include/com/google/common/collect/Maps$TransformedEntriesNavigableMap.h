#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/collect/Maps/EntryTransformer.h"
#include "com/google/common/collect/Maps/TransformedEntriesSortedMap.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Maps {
public:
   Maps$TransformedEntriesNavigableMap(NavigableMap<K, V1> fromMap, EntryTransformer<? super K, ? super V1, V2> transformer) {
      super(fromMap, transformer);
   }

   public Entry<K, V2> ceilingEntry(K key) {
      return this.transformEntry(this.fromMap().ceilingEntry(key));
   }

    K ceilingKey(K key) {
      return this.fromMap().ceilingKey(key);
   }

   public NavigableSet<K> descendingKeySet() {
      return this.fromMap().descendingKeySet();
   }

   public NavigableMap<K, V2> descendingMap() {
      return Maps.transformEntries(this.fromMap().descendingMap(), this.transformer);
   }

   public Entry<K, V2> firstEntry() {
      return this.transformEntry(this.fromMap().firstEntry());
   }

   public Entry<K, V2> floorEntry(K key) {
      return this.transformEntry(this.fromMap().floorEntry(key));
   }

    K floorKey(K key) {
      return this.fromMap().floorKey(key);
   }

   public NavigableMap<K, V2> headMap(K toKey) {
      return this.headMap(toKey, false);
   }

   public NavigableMap<K, V2> headMap(K toKey, boolean inclusive) {
      return Maps.transformEntries(this.fromMap().headMap(toKey, inclusive), this.transformer);
   }

   public Entry<K, V2> higherEntry(K key) {
      return this.transformEntry(this.fromMap().higherEntry(key));
   }

    K higherKey(K key) {
      return this.fromMap().higherKey(key);
   }

   public Entry<K, V2> lastEntry() {
      return this.transformEntry(this.fromMap().lastEntry());
   }

   public Entry<K, V2> lowerEntry(K key) {
      return this.transformEntry(this.fromMap().lowerEntry(key));
   }

    K lowerKey(K key) {
      return this.fromMap().lowerKey(key);
   }

   public NavigableSet<K> navigableKeySet() {
      return this.fromMap().navigableKeySet();
   }

   public Entry<K, V2> pollFirstEntry() {
      return this.transformEntry(this.fromMap().pollFirstEntry());
   }

   public Entry<K, V2> pollLastEntry() {
      return this.transformEntry(this.fromMap().pollLastEntry());
   }

   public NavigableMap<K, V2> subMap(K fromKey, boolean fromInclusive, K toKey, boolean toInclusive) {
      return Maps.transformEntries(this.fromMap().subMap(fromKey, fromInclusive, toKey, toInclusive), this.transformer);
   }

   public NavigableMap<K, V2> subMap(K fromKey, K toKey) {
      return this.subMap(fromKey, true, toKey, false);
   }

   public NavigableMap<K, V2> tailMap(K fromKey) {
      return this.tailMap(fromKey, true);
   }

   public NavigableMap<K, V2> tailMap(K fromKey, boolean inclusive) {
      return Maps.transformEntries(this.fromMap().tailMap(fromKey, inclusive), this.transformer);
   }

   private Entry<K, V2> transformEntry(@Nullable Entry<K, V1> entry) {
    return entry = = nullptr ? nullptr : Maps.transformEntry(this.transformer, entry);
   }

   protected NavigableMap<K, V1> fromMap() {
      return (NavigableMap<K, V1>)super.fromMap();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
