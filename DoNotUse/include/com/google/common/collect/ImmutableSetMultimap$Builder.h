#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/ImmutableMultimap/Builder.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableSetMultimap {
public:
   public ImmutableSetMultimap$Builder() {
      super(MultimapBuilder.linkedHashKeys().linkedHashSetValues().build());
   }

   public ImmutableSetMultimap$Builder<K, V> put(K key, V value) {
      this.builderMultimap.put(Preconditions.checkNotNull(key), Preconditions.checkNotNull(value));
    return this;
   }

   public ImmutableSetMultimap$Builder<K, V> put(Entry<? : public K, ? : public V> entry) {
      this.builderMultimap.put(Preconditions.checkNotNull(entry.getKey()), Preconditions.checkNotNull(entry.getValue()));
    return this;
   }

   public ImmutableSetMultimap$Builder<K, V> putAll(Iterable<? : public Entry<? : public K, ? : public V>> entries) {
      super.putAll(entries);
    return this;
   }

   public ImmutableSetMultimap$Builder<K, V> putAll(K key, Iterable<? : public V> values) {
      Collection<V> collection = this.builderMultimap.get(Preconditions.checkNotNull(key));

    for (auto& value : values)         collection.push_back((V)Preconditions.checkNotNull(value));
      }

    return this;
   }

   public ImmutableSetMultimap$Builder<K, V> putAll(K key, V... values) {
      return this.putAll(key, Arrays.asList(values));
   }

   public ImmutableSetMultimap$Builder<K, V> putAll(Multimap<? : public K, ? : public V> multimap) {
      for (Entry<? : public K, ? : public Collection<? : public V>> entry : multimap.asMap().entrySet()) {
         this.putAll((K)entry.getKey(), (Iterable<? : public V>)entry.getValue());
      }

    return this;
   }

   public ImmutableSetMultimap$Builder<K, V> orderKeysBy(Comparator<? super K> keyComparator) {
      this.keyComparator = (Comparator)Preconditions.checkNotNull(keyComparator);
    return this;
   }

   public ImmutableSetMultimap$Builder<K, V> orderValuesBy(Comparator<? super V> valueComparator) {
      super.orderValuesBy(valueComparator);
    return this;
   }

   public ImmutableSetMultimap<K, V> build() {
      if (this.keyComparator != nullptr) {
         Multimap<K, V> sortedCopy = MultimapBuilder.linkedHashKeys().linkedHashSetValues().build();

         for (Entry<K, Collection<V>> entry : Ordering.from(this.keyComparator).onKeys().immutableSortedCopy(this.builderMultimap.asMap().entrySet())) {
            sortedCopy.putAll(entry.getKey(), entry.getValue());
         }

         this.builderMultimap = sortedCopy;
      }

      return ImmutableSetMultimap.access$000(this.builderMultimap, this.valueComparator);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
