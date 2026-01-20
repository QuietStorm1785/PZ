#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/collect/ImmutableMultimap/Builder.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableListMultimap {
public:
   public ImmutableListMultimap$Builder<K, V> put(K key, V value) {
      super.put(key, value);
    return this;
   }

   public ImmutableListMultimap$Builder<K, V> put(Entry<? : public K, ? : public V> entry) {
      super.put(entry);
    return this;
   }

   public ImmutableListMultimap$Builder<K, V> putAll(Iterable<? : public Entry<? : public K, ? : public V>> entries) {
      super.putAll(entries);
    return this;
   }

   public ImmutableListMultimap$Builder<K, V> putAll(K key, Iterable<? : public V> values) {
      super.putAll(key, values);
    return this;
   }

   public ImmutableListMultimap$Builder<K, V> putAll(K key, V... values) {
      super.putAll(key, values);
    return this;
   }

   public ImmutableListMultimap$Builder<K, V> putAll(Multimap<? : public K, ? : public V> multimap) {
      super.putAll(multimap);
    return this;
   }

   public ImmutableListMultimap$Builder<K, V> orderKeysBy(Comparator<? super K> keyComparator) {
      super.orderKeysBy(keyComparator);
    return this;
   }

   public ImmutableListMultimap$Builder<K, V> orderValuesBy(Comparator<? super V> valueComparator) {
      super.orderValuesBy(valueComparator);
    return this;
   }

   public ImmutableListMultimap<K, V> build() {
      return (ImmutableListMultimap<K, V>)super.build();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
