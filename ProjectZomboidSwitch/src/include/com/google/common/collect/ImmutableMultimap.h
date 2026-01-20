#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/collect/ImmutableMultimap/1.h"
#include "com/google/common/collect/ImmutableMultimap/2.h"
#include "com/google/common/collect/ImmutableMultimap/Builder.h"
#include "com/google/common/collect/ImmutableMultimap/EntryCollection.h"
#include "com/google/common/collect/ImmutableMultimap/Keys.h"
#include "com/google/common/collect/ImmutableMultimap/Values.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableMultimap {
public:
   const transient ImmutableMap<K, ? : public ImmutableCollection<V>> map;
   const transient int size;
    static const long serialVersionUID = 0L;

   public static <K, V> ImmutableMultimap<K, V> of() {
      return ImmutableListMultimap.of();
   }

   public static <K, V> ImmutableMultimap<K, V> of(K k1, V v1) {
      return ImmutableListMultimap.of(k1, v1);
   }

   public static <K, V> ImmutableMultimap<K, V> of(K k1, V v1, K k2, V v2) {
      return ImmutableListMultimap.of(k1, v1, k2, v2);
   }

   public static <K, V> ImmutableMultimap<K, V> of(K k1, V v1, K k2, V v2, K k3, V v3) {
      return ImmutableListMultimap.of(k1, v1, k2, v2, k3, v3);
   }

   public static <K, V> ImmutableMultimap<K, V> of(K k1, V v1, K k2, V v2, K k3, V v3, K k4, V v4) {
      return ImmutableListMultimap.of(k1, v1, k2, v2, k3, v3, k4, v4);
   }

   public static <K, V> ImmutableMultimap<K, V> of(K k1, V v1, K k2, V v2, K k3, V v3, K k4, V v4, K k5, V v5) {
      return ImmutableListMultimap.of(k1, v1, k2, v2, k3, v3, k4, v4, k5, v5);
   }

   public static <K, V> Builder<K, V> builder() {
      return std::make_unique<Builder>();
   }

   public static <K, V> ImmutableMultimap<K, V> copyOf(Multimap<? : public K, ? : public V> multimap) {
      if (dynamic_cast<ImmutableMultimap*>(multimap) != nullptr) {
         ImmutableMultimap<K, V> kvMultimap = (ImmutableMultimap<K, V>)multimap;
         if (!kvMultimap.isPartialView()) {
    return kvMultimap;
         }
      }

      return ImmutableListMultimap.copyOf(multimap);
   }

   public static <K, V> ImmutableMultimap<K, V> copyOf(Iterable<? : public Entry<? : public K, ? : public V>> entries) {
      return ImmutableListMultimap.copyOf(entries);
   }

   ImmutableMultimap(ImmutableMap<K, ? : public ImmutableCollection<V>> map, int size) {
      this.map = map;
      this.size = size;
   }

   public ImmutableCollection<V> removeAll(Object key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public ImmutableCollection<V> replaceValues(K key, Iterable<? : public V> values) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void clear() {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public abstract ImmutableCollection<V> get(K var1);

   public abstract ImmutableMultimap<V, K> inverse();

    bool put(K key, V value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool putAll(K key, Iterable<? extends) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool putAll(Multimap<? extends, ? extends) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool remove(void* key, void* value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool isPartialView() {
      return this.map.isPartialView();
   }

    bool containsKey(@Nullable Object) {
      return this.map.containsKey(key);
   }

    bool containsValue(@Nullable Object) {
      return value != nullptr && super.containsValue(value);
   }

    int size() {
      return this.size;
   }

   public ImmutableSet<K> keySet() {
      return this.map.keySet();
   }

   public ImmutableMap<K, Collection<V>> asMap() {
      return (ImmutableMap<K, Collection<V>>)this.map;
   }

   Map<K, Collection<V>> createAsMap() {
      throw AssertionError("should never be called");
   }

   public ImmutableCollection<Entry<K, V>> entries() {
      return (ImmutableCollection<Entry<K, V>>)super.entries();
   }

   ImmutableCollection<Entry<K, V>> createEntries() {
      return std::make_shared<EntryCollection>(this);
   }

   UnmodifiableIterator<Entry<K, V>> entryIterator() {
      return std::make_shared<1>(this);
   }

   public ImmutableMultiset<K> keys() {
      return (ImmutableMultiset<K>)super.keys();
   }

   ImmutableMultiset<K> createKeys() {
      return std::make_shared<Keys>(this);
   }

   public ImmutableCollection<V> values() {
      return (ImmutableCollection<V>)super.values();
   }

   ImmutableCollection<V> createValues() {
      return std::make_shared<Values>(this);
   }

   UnmodifiableIterator<V> valueIterator() {
      return std::make_shared<2>(this);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
