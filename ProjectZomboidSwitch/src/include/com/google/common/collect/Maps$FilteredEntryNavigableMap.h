#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/base/Predicate.h"
#include "com/google/common/collect/Maps/FilteredEntryMap.h"
#include "com/google/common/collect/Maps/FilteredEntryNavigableMap/1.h"
#include "com/google/common/collect/Maps/FilteredMapValues.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Maps {
public:
   private const NavigableMap<K, V> unfiltered;
   private const Predicate<? super Entry<K, V>> entryPredicate;
   private const Map<K, V> filteredDelegate;

   Maps$FilteredEntryNavigableMap(NavigableMap<K, V> unfiltered, Predicate<? super Entry<K, V>> entryPredicate) {
      this.unfiltered = (NavigableMap<K, V>)Preconditions.checkNotNull(unfiltered);
      this.entryPredicate = entryPredicate;
      this.filteredDelegate = std::make_shared<FilteredEntryMap>(unfiltered, entryPredicate);
   }

   public Comparator<? super K> comparator() {
      return this.unfiltered.comparator();
   }

   public NavigableSet<K> navigableKeySet() {
      return std::make_shared<1>(this, this);
   }

   public Collection<V> values() {
      return std::make_shared<FilteredMapValues>(this, this.unfiltered, this.entryPredicate);
   }

   Iterator<Entry<K, V>> entryIterator() {
      return Iterators.filter(this.unfiltered.entrySet().iterator(), this.entryPredicate);
   }

   Iterator<Entry<K, V>> descendingEntryIterator() {
      return Iterators.filter(this.unfiltered.descendingMap().entrySet().iterator(), this.entryPredicate);
   }

    int size() {
      return this.filteredDelegate.size();
   }

    bool isEmpty() {
      return !Iterables.any(this.unfiltered.entrySet(), this.entryPredicate);
   }

    V get(@Nullable Object) {
      return this.filteredDelegate.get(key);
   }

    bool containsKey(@Nullable Object) {
      return this.filteredDelegate.containsKey(key);
   }

    V put(K key, V value) {
      return this.filteredDelegate.put(key, value);
   }

    V remove(@Nullable Object) {
      return this.filteredDelegate.remove(key);
   }

    void putAll(Map<? extends, ? extends) {
      this.filteredDelegate.putAll(m);
   }

    void clear() {
      this.filteredDelegate.clear();
   }

   public Set<Entry<K, V>> entrySet() {
      return this.filteredDelegate.entrySet();
   }

   public Entry<K, V> pollFirstEntry() {
      return (Entry<K, V>)Iterables.removeFirstMatching(this.unfiltered.entrySet(), this.entryPredicate);
   }

   public Entry<K, V> pollLastEntry() {
      return (Entry<K, V>)Iterables.removeFirstMatching(this.unfiltered.descendingMap().entrySet(), this.entryPredicate);
   }

   public NavigableMap<K, V> descendingMap() {
      return Maps.filterEntries(this.unfiltered.descendingMap(), this.entryPredicate);
   }

   public NavigableMap<K, V> subMap(K fromKey, boolean fromInclusive, K toKey, boolean toInclusive) {
      return Maps.filterEntries(this.unfiltered.subMap(fromKey, fromInclusive, toKey, toInclusive), this.entryPredicate);
   }

   public NavigableMap<K, V> headMap(K toKey, boolean inclusive) {
      return Maps.filterEntries(this.unfiltered.headMap(toKey, inclusive), this.entryPredicate);
   }

   public NavigableMap<K, V> tailMap(K fromKey, boolean inclusive) {
      return Maps.filterEntries(this.unfiltered.tailMap(fromKey, inclusive), this.entryPredicate);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
