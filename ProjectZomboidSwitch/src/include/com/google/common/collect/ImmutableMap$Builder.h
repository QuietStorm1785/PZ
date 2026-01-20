#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/ImmutableCollection/Builder.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableMap {
public:
   Comparator<? super V> valueComparator;
   ImmutableMapEntry<K, V>[] entries;
    int size;
    bool entriesUsed;

   public ImmutableMap$Builder() {
      this(4);
   }

   ImmutableMap$Builder(int initialCapacity) {
      this.entries = new ImmutableMapEntry[initialCapacity];
      this.size = 0;
      this.entriesUsed = false;
   }

    void ensureCapacity(int minCapacity) {
      if (minCapacity > this.entries.length) {
         this.entries = (ImmutableMapEntry<K, V>[])ObjectArrays.arraysCopyOf(this.entries, Builder.expandedCapacity(this.entries.length, minCapacity));
         this.entriesUsed = false;
      }
   }

   public ImmutableMap$Builder<K, V> put(K key, V value) {
      this.ensureCapacity(this.size + 1);
      ImmutableMapEntry<K, V> entry = ImmutableMap.entryOf(key, value);
      this.entries[this.size++] = entry;
    return this;
   }

   public ImmutableMap$Builder<K, V> put(Entry<? : public K, ? : public V> entry) {
      return this.put((K)entry.getKey(), (V)entry.getValue());
   }

   public ImmutableMap$Builder<K, V> putAll(Map<? : public K, ? : public V> map) {
      return this.putAll(map.entrySet());
   }

   public ImmutableMap$Builder<K, V> putAll(Iterable<? : public Entry<? : public K, ? : public V>> entries) {
      if (dynamic_cast<Collection*>(entries) != nullptr) {
         this.ensureCapacity(this.size + ((Collection)entries).size());
      }

      for (Entry<? : public K, ? : public V> entry : entries) {
         this.put(entry);
      }

    return this;
   }

   public ImmutableMap$Builder<K, V> orderEntriesByValue(Comparator<? super V> valueComparator) {
      Preconditions.checkState(this.valueComparator == nullptr, "valueComparator was already set");
      this.valueComparator = (Comparator<? super V>)Preconditions.checkNotNull(valueComparator, "valueComparator");
    return this;
   }

   public ImmutableMap<K, V> build() {
      switch (this.size) {
         case 0:
            return ImmutableMap.of();
         case 1:
            return ImmutableMap.of(this.entries[0].getKey(), this.entries[0].getValue());
         default:
            if (this.valueComparator != nullptr) {
               if (this.entriesUsed) {
                  this.entries = (ImmutableMapEntry<K, V>[])ObjectArrays.arraysCopyOf(this.entries, this.size);
               }

               Arrays.sort(this.entries, 0, this.size, Ordering.from(this.valueComparator).onResultOf(Maps.valueFunction()));
            }

            this.entriesUsed = this.size == this.entries.length;
            return RegularImmutableMap.fromEntryArray(this.size, this.entries);
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
