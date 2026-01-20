#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/collect/ImmutableBiMap/Builder.h"
#include "com/google/common/collect/ImmutableBiMap/SerializedForm.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableBiMap {
public:
   public static <K, V> ImmutableBiMap<K, V> of() {
      return RegularImmutableBiMap.EMPTY;
   }

   public static <K, V> ImmutableBiMap<K, V> of(K k1, V v1) {
      return std::make_shared<SingletonImmutableBiMap>(k1, v1);
   }

   public static <K, V> ImmutableBiMap<K, V> of(K k1, V v1, K k2, V v2) {
      return RegularImmutableBiMap.fromEntries(new Entry[]{entryOf(k1, v1), entryOf(k2, v2)});
   }

   public static <K, V> ImmutableBiMap<K, V> of(K k1, V v1, K k2, V v2, K k3, V v3) {
      return RegularImmutableBiMap.fromEntries(new Entry[]{entryOf(k1, v1), entryOf(k2, v2), entryOf(k3, v3)});
   }

   public static <K, V> ImmutableBiMap<K, V> of(K k1, V v1, K k2, V v2, K k3, V v3, K k4, V v4) {
      return RegularImmutableBiMap.fromEntries(new Entry[]{entryOf(k1, v1), entryOf(k2, v2), entryOf(k3, v3), entryOf(k4, v4)});
   }

   public static <K, V> ImmutableBiMap<K, V> of(K k1, V v1, K k2, V v2, K k3, V v3, K k4, V v4, K k5, V v5) {
      return RegularImmutableBiMap.fromEntries(new Entry[]{entryOf(k1, v1), entryOf(k2, v2), entryOf(k3, v3), entryOf(k4, v4), entryOf(k5, v5)});
   }

   public static <K, V> Builder<K, V> builder() {
      return std::make_unique<Builder>();
   }

   public static <K, V> ImmutableBiMap<K, V> copyOf(Map<? : public K, ? : public V> map) {
      if (dynamic_cast<ImmutableBiMap*>(map) != nullptr) {
         ImmutableBiMap<K, V> bimap = (ImmutableBiMap<K, V>)map;
         if (!bimap.isPartialView()) {
    return bimap;
         }
      }

    return copyOf();
   }

   public static <K, V> ImmutableBiMap<K, V> copyOf(Iterable<? : public Entry<? : public K, ? : public V>> entries) {
      Entry<K, V>[] entryArray = (Entry<K, V>[])Iterables.toArray(entries, EMPTY_ENTRY_ARRAY);
      switch (entryArray.length) {
         case 0:
    return of();
         case 1:
            Entry<K, V> entry = entryArray[0];
    return of();
         default:
            return RegularImmutableBiMap.fromEntries(entryArray);
      }
   }

   ImmutableBiMap() {
   }

   public abstract ImmutableBiMap<V, K> inverse();

   public ImmutableSet<V> values() {
      return this.inverse().keySet();
   }

    V forcePut(K key, V value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void* writeReplace() {
      return std::make_shared<SerializedForm>(this);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
