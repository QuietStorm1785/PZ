#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class Maps {
public:
   private const NavigableMap<K, ? : public V> delegate;
   private transient Maps$UnmodifiableNavigableMap<K, V> descendingMap;

   Maps$UnmodifiableNavigableMap(NavigableMap<K, ? : public V> delegate) {
      this.delegate = delegate;
   }

   Maps$UnmodifiableNavigableMap(NavigableMap<K, ? : public V> delegate, Maps$UnmodifiableNavigableMap<K, V> descendingMap) {
      this.delegate = delegate;
      this.descendingMap = descendingMap;
   }

   protected SortedMap<K, V> delegate() {
      return Collections.unmodifiableSortedMap(this.delegate);
   }

   public Entry<K, V> lowerEntry(K key) {
      return Maps.access$800(this.delegate.lowerEntry(key));
   }

    K lowerKey(K key) {
      return this.delegate.lowerKey(key);
   }

   public Entry<K, V> floorEntry(K key) {
      return Maps.access$800(this.delegate.floorEntry(key));
   }

    K floorKey(K key) {
      return this.delegate.floorKey(key);
   }

   public Entry<K, V> ceilingEntry(K key) {
      return Maps.access$800(this.delegate.ceilingEntry(key));
   }

    K ceilingKey(K key) {
      return this.delegate.ceilingKey(key);
   }

   public Entry<K, V> higherEntry(K key) {
      return Maps.access$800(this.delegate.higherEntry(key));
   }

    K higherKey(K key) {
      return this.delegate.higherKey(key);
   }

   public Entry<K, V> firstEntry() {
      return Maps.access$800(this.delegate.firstEntry());
   }

   public Entry<K, V> lastEntry() {
      return Maps.access$800(this.delegate.lastEntry());
   }

   public const Entry<K, V> pollFirstEntry() {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public const Entry<K, V> pollLastEntry() {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public NavigableMap<K, V> descendingMap() {
      Maps$UnmodifiableNavigableMap<K, V> result = this.descendingMap;
    return result = = nullptr ? (this.descendingMap = new Maps$UnmodifiableNavigableMap<>(this.delegate.descendingMap(), this)) : result;
   }

   public Set<K> keySet() {
      return this.navigableKeySet();
   }

   public NavigableSet<K> navigableKeySet() {
      return Sets.unmodifiableNavigableSet(this.delegate.navigableKeySet());
   }

   public NavigableSet<K> descendingKeySet() {
      return Sets.unmodifiableNavigableSet(this.delegate.descendingKeySet());
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

   public NavigableMap<K, V> subMap(K fromKey, boolean fromInclusive, K toKey, boolean toInclusive) {
      return Maps.unmodifiableNavigableMap(this.delegate.subMap(fromKey, fromInclusive, toKey, toInclusive));
   }

   public NavigableMap<K, V> headMap(K toKey, boolean inclusive) {
      return Maps.unmodifiableNavigableMap(this.delegate.headMap(toKey, inclusive));
   }

   public NavigableMap<K, V> tailMap(K fromKey, boolean inclusive) {
      return Maps.unmodifiableNavigableMap(this.delegate.tailMap(fromKey, inclusive));
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
