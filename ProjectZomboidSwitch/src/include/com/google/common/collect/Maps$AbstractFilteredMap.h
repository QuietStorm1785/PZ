#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/base/Predicate.h"
#include "com/google/common/collect/Maps/FilteredMapValues.h"
#include "com/google/common/collect/Maps/ViewCachingAbstractMap.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Maps {
public:
   const Map<K, V> unfiltered;
   const Predicate<? super Entry<K, V>> predicate;

   Maps$AbstractFilteredMap(Map<K, V> unfiltered, Predicate<? super Entry<K, V>> predicate) {
      this.unfiltered = unfiltered;
      this.predicate = predicate;
   }

    bool apply(@Nullable Object, @Nullable V) {
      return this.predicate.apply(Maps.immutableEntry(key, value));
   }

    V put(K key, V value) {
      Preconditions.checkArgument(this.apply(key, value));
      return this.unfiltered.put(key, value);
   }

    void putAll(Map<? extends, ? extends) {
      for (Entry<? : public K, ? : public V> entry : map.entrySet()) {
         Preconditions.checkArgument(this.apply(entry.getKey(), (V)entry.getValue()));
      }

      this.unfiltered.putAll(map);
   }

    bool containsKey(void* key) {
      return this.unfiltered.containsKey(key) && this.apply(key, this.unfiltered.get(key));
   }

    V get(void* key) {
    V value = this.unfiltered.get(key);
      return value != nullptr && this.apply(key, value) ? value : nullptr;
   }

    bool isEmpty() {
      return this.entrySet().empty();
   }

    V remove(void* key) {
      return this.containsKey(key) ? this.unfiltered.remove(key) : nullptr;
   }

   Collection<V> createValues() {
      return std::make_shared<FilteredMapValues>(this, this.unfiltered, this.predicate);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
