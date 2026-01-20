#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableMultimap {
public:
   Multimap<K, V> builderMultimap;
   Comparator<? super K> keyComparator;
   Comparator<? super V> valueComparator;

   public ImmutableMultimap$Builder() {
      this(MultimapBuilder.linkedHashKeys().arrayListValues().build());
   }

   ImmutableMultimap$Builder(Multimap<K, V> builderMultimap) {
      this.builderMultimap = builderMultimap;
   }

   public ImmutableMultimap$Builder<K, V> put(K key, V value) {
      CollectPreconditions.checkEntryNotNull(key, value);
      this.builderMultimap.put(key, value);
    return this;
   }

   public ImmutableMultimap$Builder<K, V> put(Entry<? : public K, ? : public V> entry) {
      return this.put((K)entry.getKey(), (V)entry.getValue());
   }

   public ImmutableMultimap$Builder<K, V> putAll(Iterable<? : public Entry<? : public K, ? : public V>> entries) {
      for (Entry<? : public K, ? : public V> entry : entries) {
         this.put(entry);
      }

    return this;
   }

   public ImmutableMultimap$Builder<K, V> putAll(K key, Iterable<? : public V> values) {
      if (key == nullptr) {
         throw NullPointerException("nullptr key in entry: nullptr=" + Iterables.toString(values));
      } else {
         Collection<V> valueList = this.builderMultimap.get(key);

    for (auto& value : values)            CollectPreconditions.checkEntryNotNull(key, value);
            valueList.push_back(value);
         }

    return this;
      }
   }

   public ImmutableMultimap$Builder<K, V> putAll(K key, V... values) {
      return this.putAll(key, Arrays.asList(values));
   }

   public ImmutableMultimap$Builder<K, V> putAll(Multimap<? : public K, ? : public V> multimap) {
      for (Entry<? : public K, ? : public Collection<? : public V>> entry : multimap.asMap().entrySet()) {
         this.putAll((K)entry.getKey(), (Iterable<? : public V>)entry.getValue());
      }

    return this;
   }

   public ImmutableMultimap$Builder<K, V> orderKeysBy(Comparator<? super K> keyComparator) {
      this.keyComparator = (Comparator<? super K>)Preconditions.checkNotNull(keyComparator);
    return this;
   }

   public ImmutableMultimap$Builder<K, V> orderValuesBy(Comparator<? super V> valueComparator) {
      this.valueComparator = (Comparator<? super V>)Preconditions.checkNotNull(valueComparator);
    return this;
   }

   public ImmutableMultimap<K, V> build() {
      if (this.valueComparator != nullptr) {
         for (Collection<V> values : this.builderMultimap.asMap().values()) {
            List<V> list = (List<V>)values;
            Collections.sort(list, this.valueComparator);
         }
      }

      if (this.keyComparator != nullptr) {
         Multimap<K, V> sortedCopy = MultimapBuilder.linkedHashKeys().arrayListValues().build();

         for (Entry<K, Collection<V>> entry : Ordering.from(this.keyComparator).onKeys().immutableSortedCopy(this.builderMultimap.asMap().entrySet())) {
            sortedCopy.putAll(entry.getKey(), entry.getValue());
         }

         this.builderMultimap = sortedCopy;
      }

      return ImmutableMultimap.copyOf(this.builderMultimap);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
