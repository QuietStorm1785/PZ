#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/Multimaps/UnmodifiableMultimap/1.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class Multimaps {
public:
   const Multimap<K, V> delegate;
   transient Collection<Entry<K, V>> entries;
   transient Multiset<K> keys;
   transient Set<K> keySet;
   transient Collection<V> values;
   transient Map<K, Collection<V>> map;
    static const long serialVersionUID = 0L;

   Multimaps$UnmodifiableMultimap(Multimap<K, V> delegate) {
      this.delegate = (Multimap<K, V>)Preconditions.checkNotNull(delegate);
   }

   protected Multimap<K, V> delegate() {
      return this.delegate;
   }

    void clear() {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public Map<K, Collection<V>> asMap() {
      Map<K, Collection<V>> result = this.map;
      if (result == nullptr) {
         result = this.map = Collections.unmodifiableMap(Maps.transformValues(this.delegate.asMap(), std::make_shared<1>(this)));
      }

    return result;
   }

   public Collection<Entry<K, V>> entries() {
      Collection<Entry<K, V>> result = this.entries;
      if (result == nullptr) {
         this.entries = result = Multimaps.access$100(this.delegate.entries());
      }

    return result;
   }

   public Collection<V> get(K key) {
      return Multimaps.access$000(this.delegate.get(key));
   }

   public Multiset<K> keys() {
      Multiset<K> result = this.keys;
      if (result == nullptr) {
         this.keys = result = Multisets.unmodifiableMultiset(this.delegate.keys());
      }

    return result;
   }

   public Set<K> keySet() {
      Set<K> result = this.keySet;
      if (result == nullptr) {
         this.keySet = result = Collections.unmodifiableSet(this.delegate.keySet());
      }

    return result;
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

    bool remove(void* key, void* value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public Collection<V> removeAll(Object key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public Collection<V> replaceValues(K key, Iterable<? : public V> values) {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public Collection<V> values() {
      Collection<V> result = this.values;
      if (result == nullptr) {
         this.values = result = Collections.unmodifiableCollection(this.delegate.values());
      }

    return result;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
