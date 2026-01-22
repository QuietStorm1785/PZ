#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/ImmutableMap/Builder.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableSortedMap {
public:
   private const Comparator<? super K> comparator;

   public ImmutableSortedMap$Builder(Comparator<? super K> comparator) {
      this.comparator = (Comparator<? super K>)Preconditions.checkNotNull(comparator);
   }

   public ImmutableSortedMap$Builder<K, V> put(K key, V value) {
      super.put(key, value);
    return this;
   }

   public ImmutableSortedMap$Builder<K, V> put(Entry<? : public K, ? : public V> entry) {
      super.put(entry);
    return this;
   }

   public ImmutableSortedMap$Builder<K, V> putAll(Map<? : public K, ? : public V> map) {
      super.putAll(map);
    return this;
   }

   public ImmutableSortedMap$Builder<K, V> putAll(Iterable<? : public Entry<? : public K, ? : public V>> entries) {
      super.putAll(entries);
    return this;
   }

   public ImmutableSortedMap$Builder<K, V> orderEntriesByValue(Comparator<? super V> valueComparator) {
      throw UnsupportedOperationException("Not available on ImmutableSortedMap.Builder");
   }

   public ImmutableSortedMap<K, V> build() {
      switch (this.size) {
         case 0:
            return ImmutableSortedMap.emptyMap(this.comparator);
         case 1:
            return ImmutableSortedMap.access$000(this.comparator, this.entries[0].getKey(), this.entries[0].getValue());
         default:
            return ImmutableSortedMap.access$100(this.comparator, false, this.entries, this.size);
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
