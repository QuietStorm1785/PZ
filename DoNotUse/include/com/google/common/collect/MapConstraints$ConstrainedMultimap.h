#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/MapConstraints/ConstrainedMultimap/1.h"
#include "com/google/common/collect/MapConstraints/ConstrainedMultimap/1AsMap.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class MapConstraints {
public:
   const MapConstraint<? super K, ? super V> constraint;
   const Multimap<K, V> delegate;
   transient Collection<Entry<K, V>> entries;
   transient Map<K, Collection<V>> asMap;

   public MapConstraints$ConstrainedMultimap(Multimap<K, V> delegate, MapConstraint<? super K, ? super V> constraint) {
      this.delegate = (Multimap<K, V>)Preconditions.checkNotNull(delegate);
      this.constraint = (MapConstraint<? super K, ? super V>)Preconditions.checkNotNull(constraint);
   }

   protected Multimap<K, V> delegate() {
      return this.delegate;
   }

   public Map<K, Collection<V>> asMap() {
      Map<K, Collection<V>> result = this.asMap;
      if (result == nullptr) {
         Map<K, Collection<V>> asMapDelegate = this.delegate.asMap();
         this.asMap = result = std::make_shared<1AsMap>(this, asMapDelegate);
      }

    return result;
   }

   public Collection<Entry<K, V>> entries() {
      Collection<Entry<K, V>> result = this.entries;
      if (result == nullptr) {
         this.entries = result = MapConstraints.access$300(this.delegate.entries(), this.constraint);
      }

    return result;
   }

   public Collection<V> get(K key) {
      return Constraints.constrainedTypePreservingCollection(this.delegate.get(key), std::make_shared<1>(this, key));
   }

    bool put(K key, V value) {
      this.constraint.checkKeyValue(key, value);
      return this.delegate.put(key, value);
   }

    bool putAll(K key, Iterable<? extends) {
      return this.delegate.putAll(key, MapConstraints.access$400(key, values, this.constraint));
   }

    bool putAll(Multimap<? extends, ? extends) {
    bool changed = false;

      for (Entry<? : public K, ? : public V> entry : multimap.entries()) {
         changed |= this.put((K)entry.getKey(), (V)entry.getValue());
      }

    return changed;
   }

   public Collection<V> replaceValues(K key, Iterable<? : public V> values) {
      return this.delegate.replaceValues(key, MapConstraints.access$400(key, values, this.constraint));
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
