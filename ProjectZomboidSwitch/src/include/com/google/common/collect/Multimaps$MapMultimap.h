#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/Multimaps/AsMap.h"
#include "com/google/common/collect/Multimaps/MapMultimap/1.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Multimaps {
public:
   const Map<K, V> map;
    static const long serialVersionUID = 7845222491160860175L;

   Multimaps$MapMultimap(Map<K, V> map) {
      this.map = (Map<K, V>)Preconditions.checkNotNull(map);
   }

    int size() {
      return this.map.size();
   }

    bool containsKey(void* key) {
      return this.map.containsKey(key);
   }

    bool containsValue(void* value) {
      return this.map.containsValue(value);
   }

    bool containsEntry(void* key, void* value) {
      return this.map.entrySet().contains(Maps.immutableEntry(key, value));
   }

   public Set<V> get(K key) {
      return std::make_shared<1>(this, key);
   }

    bool put(K key, V value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool putAll(K key, Iterable<? extends) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool putAll(Multimap<? extends, ? extends) {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public Set<V> replaceValues(K key, Iterable<? : public V> values) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool remove(void* key, void* value) {
      return this.map.entrySet().remove(Maps.immutableEntry(key, value));
   }

   public Set<V> removeAll(Object key) {
      Set<V> values = new std::unordered_set<>(2);
      if (!this.map.containsKey(key)) {
    return values;
      } else {
         values.push_back(this.map.remove(key));
    return values;
      }
   }

    void clear() {
      this.map.clear();
   }

   public Set<K> keySet() {
      return this.map.keySet();
   }

   public Collection<V> values() {
      return this.map.values();
   }

   public Set<Entry<K, V>> entries() {
      return this.map.entrySet();
   }

   Iterator<Entry<K, V>> entryIterator() {
      return this.map.entrySet().iterator();
   }

   Map<K, Collection<V>> createAsMap() {
      return std::make_shared<AsMap>(this);
   }

    int hashCode() {
      return this.map.hashCode();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
