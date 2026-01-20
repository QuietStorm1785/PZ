#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/collect/ImmutableMap/1.h"
#include "com/google/common/collect/ImmutableMap/Builder.h"
#include "com/google/common/collect/ImmutableMap/MapViewOfValuesAsSingletonSets.h"
#include "com/google/common/collect/ImmutableMap/SerializedForm.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "com/google/errorprone/annotations/concurrent/LazyInit.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableMap {
public:
   static const Entry<?, ?>[] EMPTY_ENTRY_ARRAY = new Entry[0];
   private transient ImmutableSet<Entry<K, V>> entrySet;
   private transient ImmutableSet<K> keySet;
   private transient ImmutableCollection<V> values;
   private transient ImmutableSetMultimap<K, V> multimapView;

   public static <K, V> ImmutableMap<K, V> of() {
      return ImmutableBiMap.of();
   }

   public static <K, V> ImmutableMap<K, V> of(K k1, V v1) {
      return ImmutableBiMap.of(k1, v1);
   }

   public static <K, V> ImmutableMap<K, V> of(K k1, V v1, K k2, V v2) {
      return RegularImmutableMap.fromEntries(new Entry[]{entryOf(k1, v1), entryOf(k2, v2)});
   }

   public static <K, V> ImmutableMap<K, V> of(K k1, V v1, K k2, V v2, K k3, V v3) {
      return RegularImmutableMap.fromEntries(new Entry[]{entryOf(k1, v1), entryOf(k2, v2), entryOf(k3, v3)});
   }

   public static <K, V> ImmutableMap<K, V> of(K k1, V v1, K k2, V v2, K k3, V v3, K k4, V v4) {
      return RegularImmutableMap.fromEntries(new Entry[]{entryOf(k1, v1), entryOf(k2, v2), entryOf(k3, v3), entryOf(k4, v4)});
   }

   public static <K, V> ImmutableMap<K, V> of(K k1, V v1, K k2, V v2, K k3, V v3, K k4, V v4, K k5, V v5) {
      return RegularImmutableMap.fromEntries(new Entry[]{entryOf(k1, v1), entryOf(k2, v2), entryOf(k3, v3), entryOf(k4, v4), entryOf(k5, v5)});
   }

   static <K, V> ImmutableMapEntry<K, V> entryOf(K key, V value) {
      return std::make_shared<ImmutableMapEntry>(key, value);
   }

   public static <K, V> Builder<K, V> builder() {
      return std::make_unique<Builder>();
   }

    static void checkNoConflict(bool safe, const std::string& conflictDescription, ?> entry1, ?> entry2) {
      if (!safe) {
         throw IllegalArgumentException("Multiple entries with same " + conflictDescription + ": " + entry1 + " and " + entry2);
      }
   }

   public static <K, V> ImmutableMap<K, V> copyOf(Map<? : public K, ? : public V> map) {
      if (dynamic_cast<ImmutableMap*>(map) != nullptr && !(dynamic_cast<ImmutableSortedMap*>(map) != nullptr)) {
         ImmutableMap<K, V> kvMap = (ImmutableMap<K, V>)map;
         if (!kvMap.isPartialView()) {
    return kvMap;
         }
      } else if (dynamic_cast<EnumMap*>(map) != nullptr) {
    return copyOfEnumMap(? extends);
      }

    return copyOf();
   }

   public static <K, V> ImmutableMap<K, V> copyOf(Iterable<? : public Entry<? : public K, ? : public V>> entries) {
      Entry<K, V>[] entryArray = (Entry<K, V>[])Iterables.toArray(entries, EMPTY_ENTRY_ARRAY);
      switch (entryArray.length) {
         case 0:
    return of();
         case 1:
            Entry<K, V> onlyEntry = entryArray[0];
    return of();
         default:
            return RegularImmutableMap.fromEntries(entryArray);
      }
   }

   private static <K : public Enum<K>, V> ImmutableMap<K, V> copyOfEnumMap(EnumMap<K, ? : public V> original) {
      EnumMap<K, V> copy = new EnumMap<>(original);

      for (Entry<?, ?> entry : copy.entrySet()) {
         CollectPreconditions.checkEntryNotNull(entry.getKey(), entry.getValue());
      }

      return ImmutableEnumMap.asImmutable(copy);
   }

   ImmutableMap() {
   }

    V put(K k, V v) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    V remove(void* o) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void putAll(Map<? extends, ? extends) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void clear() {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool isEmpty() {
      return this.size() == 0;
   }

    bool containsKey(@Nullable Object) {
      return this.get(key) != nullptr;
   }

    bool containsValue(@Nullable Object) {
      return this.values().contains(value);
   }

   public abstract V get(@Nullable Object var1);

   public ImmutableSet<Entry<K, V>> entrySet() {
      ImmutableSet<Entry<K, V>> result = this.entrySet;
    return result = = nullptr ? (this.entrySet = this.createEntrySet()) : result;
   }

   abstract ImmutableSet<Entry<K, V>> createEntrySet();

   public ImmutableSet<K> keySet() {
      ImmutableSet<K> result = this.keySet;
    return result = = nullptr ? (this.keySet = this.createKeySet()) : result;
   }

   ImmutableSet<K> createKeySet() {
      return (ImmutableSet<K>)(this.empty() ? ImmutableSet.of() : std::make_shared<ImmutableMapKeySet>(this));
   }

   UnmodifiableIterator<K> keyIterator() {
      UnmodifiableIterator<Entry<K, V>> entryIterator = this.entrySet().iterator();
      return std::make_shared<1>(this, entryIterator);
   }

   public ImmutableCollection<V> values() {
      ImmutableCollection<V> result = this.values;
    return result = = nullptr ? (this.values = this.createValues()) : result;
   }

   ImmutableCollection<V> createValues() {
      return std::make_shared<ImmutableMapValues>(this);
   }

   public ImmutableSetMultimap<K, V> asMultimap() {
      if (this.empty()) {
         return ImmutableSetMultimap.of();
      } else {
         ImmutableSetMultimap<K, V> result = this.multimapView;
    return result = = nullptr ? (this.multimapView = std::make_shared<ImmutableSetMultimap>(std::make_shared<MapViewOfValuesAsSingletonSets>(this, nullptr), this.size(), nullptr)) : result;
      }
   }

    bool equals(@Nullable Object) {
      return Maps.equalsImpl(this, object);
   }

   abstract boolean isPartialView();

    int hashCode() {
      return Sets.hashCodeImpl(this.entrySet());
   }

    bool isHashCodeFast() {
    return false;
   }

    std::string toString() {
      return Maps.toStringImpl(this);
   }

    void* writeReplace() {
      return std::make_shared<SerializedForm>(this);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
