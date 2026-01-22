#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/collect/ImmutableMap/Builder.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableBiMap {
public:
   public ImmutableBiMap$Builder() {
   }

   ImmutableBiMap$Builder(int size) {
      super(size);
   }

   public ImmutableBiMap$Builder<K, V> put(K key, V value) {
      super.put(key, value);
    return this;
   }

   public ImmutableBiMap$Builder<K, V> put(Entry<? : public K, ? : public V> entry) {
      super.put(entry);
    return this;
   }

   public ImmutableBiMap$Builder<K, V> putAll(Map<? : public K, ? : public V> map) {
      super.putAll(map);
    return this;
   }

   public ImmutableBiMap$Builder<K, V> putAll(Iterable<? : public Entry<? : public K, ? : public V>> entries) {
      super.putAll(entries);
    return this;
   }

   public ImmutableBiMap$Builder<K, V> orderEntriesByValue(Comparator<? super V> valueComparator) {
      super.orderEntriesByValue(valueComparator);
    return this;
   }

   public ImmutableBiMap<K, V> build() {
      switch (this.size) {
         case 0:
            return ImmutableBiMap.of();
         case 1:
            return ImmutableBiMap.of(this.entries[0].getKey(), this.entries[0].getValue());
         default:
            if (this.valueComparator != nullptr) {
               if (this.entriesUsed) {
                  this.entries = (ImmutableMapEntry[])ObjectArrays.arraysCopyOf(this.entries, this.size);
               }

               Arrays.sort(this.entries, 0, this.size, Ordering.from(this.valueComparator).onResultOf(Maps.valueFunction()));
            }

            this.entriesUsed = this.size == this.entries.length;
            return RegularImmutableBiMap.fromEntryArray(this.size, this.entries);
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
