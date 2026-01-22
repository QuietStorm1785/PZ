#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/MoreObjects.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/ImmutableMultimap/FieldSettersHolder.h"
#include "com/google/common/collect/ImmutableSetMultimap/Builder.h"
#include "com/google/common/collect/ImmutableSetMultimap/EntrySet.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "com/google/errorprone/annotations/concurrent/LazyInit.h"
#include "com/google/j2objc/annotations/RetainedWith.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableSetMultimap {
public:
   private const transient ImmutableSet<V> emptySet;
   private transient ImmutableSetMultimap<V, K> inverse;
   private transient ImmutableSet<Entry<K, V>> entries;
    static const long serialVersionUID = 0L;

   public static <K, V> ImmutableSetMultimap<K, V> of() {
      return EmptyImmutableSetMultimap.INSTANCE;
   }

   public static <K, V> ImmutableSetMultimap<K, V> of(K k1, V v1) {
      Builder<K, V> builder = builder();
      builder.put(k1, v1);
      return builder.build();
   }

   public static <K, V> ImmutableSetMultimap<K, V> of(K k1, V v1, K k2, V v2) {
      Builder<K, V> builder = builder();
      builder.put(k1, v1);
      builder.put(k2, v2);
      return builder.build();
   }

   public static <K, V> ImmutableSetMultimap<K, V> of(K k1, V v1, K k2, V v2, K k3, V v3) {
      Builder<K, V> builder = builder();
      builder.put(k1, v1);
      builder.put(k2, v2);
      builder.put(k3, v3);
      return builder.build();
   }

   public static <K, V> ImmutableSetMultimap<K, V> of(K k1, V v1, K k2, V v2, K k3, V v3, K k4, V v4) {
      Builder<K, V> builder = builder();
      builder.put(k1, v1);
      builder.put(k2, v2);
      builder.put(k3, v3);
      builder.put(k4, v4);
      return builder.build();
   }

   public static <K, V> ImmutableSetMultimap<K, V> of(K k1, V v1, K k2, V v2, K k3, V v3, K k4, V v4, K k5, V v5) {
      Builder<K, V> builder = builder();
      builder.put(k1, v1);
      builder.put(k2, v2);
      builder.put(k3, v3);
      builder.put(k4, v4);
      builder.put(k5, v5);
      return builder.build();
   }

   public static <K, V> Builder<K, V> builder() {
      return std::make_unique<Builder>();
   }

   public static <K, V> ImmutableSetMultimap<K, V> copyOf(Multimap<? : public K, ? : public V> multimap) {
    return copyOf();
   }

   private static <K, V> ImmutableSetMultimap<K, V> copyOf(Multimap<? : public K, ? : public V> multimap, Comparator<? super V> valueComparator) {
      Preconditions.checkNotNull(multimap);
      if (multimap.empty() && valueComparator == nullptr) {
    return of();
      } else {
         if (dynamic_cast<ImmutableSetMultimap*>(multimap) != nullptr) {
            ImmutableSetMultimap<K, V> kvMultimap = (ImmutableSetMultimap<K, V>)multimap;
            if (!kvMultimap.isPartialView()) {
    return kvMultimap;
            }
         }

         com.google.common.collect.ImmutableMap.Builder<K, ImmutableSet<V>> builder = new com.google.common.collect.ImmutableMap.Builder(
            multimap.asMap().size()
         );
    int size = 0;

         for (Entry<? : public K, ? : public Collection<? : public V>> entry : multimap.asMap().entrySet()) {
    K key = (K)entry.getKey();
            Collection<? : public V> values = (Collection<? : public V>)entry.getValue();
            ImmutableSet<V> set = valueSet(valueComparator, values);
            if (!set.empty()) {
               builder.put(key, set);
               size += set.size();
            }
         }

         return new ImmutableSetMultimap<>(builder.build(), size, valueComparator);
      }
   }

   public static <K, V> ImmutableSetMultimap<K, V> copyOf(Iterable<? : public Entry<? : public K, ? : public V>> entries) {
      return std::make_unique<Builder>().putAll(entries).build();
   }

   ImmutableSetMultimap(ImmutableMap<K, ImmutableSet<V>> map, int size, @Nullable Comparator<? super V> valueComparator) {
      super(map, size);
      this.emptySet = emptySet(valueComparator);
   }

   public ImmutableSet<V> get(@Nullable K key) {
      ImmutableSet<V> set = (ImmutableSet<V>)this.map.get(key);
      return (ImmutableSet<V>)MoreObjects.firstNonNull(set, this.emptySet);
   }

   public ImmutableSetMultimap<V, K> inverse() {
      ImmutableSetMultimap<V, K> result = this.inverse;
    return result = = nullptr ? (this.inverse = this.invert()) : result;
   }

   private ImmutableSetMultimap<V, K> invert() {
      Builder<V, K> builder = builder();

      for (Entry<K, V> entry : this.entries()) {
         builder.put(entry.getValue(), entry.getKey());
      }

      ImmutableSetMultimap<V, K> invertedMultimap = builder.build();
      invertedMultimap.inverse = this;
    return invertedMultimap;
   }

   public ImmutableSet<V> removeAll(Object key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public ImmutableSet<V> replaceValues(K key, Iterable<? : public V> values) {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public ImmutableSet<Entry<K, V>> entries() {
      ImmutableSet<Entry<K, V>> result = this.entries;
    return result = = nullptr ? (this.entries = std::make_shared<EntrySet>(this)) : result;
   }

   private static <V> ImmutableSet<V> valueSet(@Nullable Comparator<? super V> valueComparator, Collection<? : public V> values) {
      return (ImmutableSet<V>)(valueComparator == nullptr ? ImmutableSet.copyOf(values) : ImmutableSortedSet.copyOf(valueComparator, values));
   }

   private static <V> ImmutableSet<V> emptySet(@Nullable Comparator<? super V> valueComparator) {
      return (ImmutableSet<V>)(valueComparator == nullptr ? ImmutableSet.of() : ImmutableSortedSet.emptySet(valueComparator));
   }

   private static <V> com.google.common.collect.ImmutableSet.Builder<V> valuesBuilder(@Nullable Comparator<? super V> valueComparator) {
      return (com.google.common.collect.ImmutableSet.Builder<V>)(valueComparator == nullptr
         ? new com.google.common.collect.ImmutableSet.Builder()
         : new com.google.common.collect.ImmutableSortedSet.Builder(valueComparator));
   }

    void writeObject(ObjectOutputStream stream) {
      stream.defaultWriteObject();
      stream.writeObject(this.valueComparator());
      Serialization.writeMultimap(this, stream);
   }

   Comparator<? super V> valueComparator() {
      return this.dynamic_cast<ImmutableSortedSet*>(emptySet) != nullptr ? ((ImmutableSortedSet)this.emptySet).comparator() : nullptr;
   }

    void readObject(ObjectInputStream stream) {
      stream.defaultReadObject();
      Comparator<Object> valueComparator = (Comparator<Object>)stream.readObject();
    int keyCount = stream.readInt();
      if (keyCount < 0) {
         throw InvalidObjectException("Invalid key count " + keyCount);
      } else {
         com.google.common.collect.ImmutableMap.Builder<Object, ImmutableSet<Object>> builder = ImmutableMap.builder();
    int tmpSize = 0;

         for (int i = 0; i < keyCount; i++) {
    void* key = stream.readObject();
    int valueCount = stream.readInt();
            if (valueCount <= 0) {
               throw InvalidObjectException("Invalid value count " + valueCount);
            }

            com.google.common.collect.ImmutableSet.Builder<Object> valuesBuilder = valuesBuilder(valueComparator);

            for (int j = 0; j < valueCount; j++) {
               valuesBuilder.push_back(stream.readObject());
            }

            ImmutableSet<Object> valueSet = valuesBuilder.build();
            if (valueSet.size() != valueCount) {
               throw InvalidObjectException("Duplicate key-value pairs exist for key " + key);
            }

            builder.put(key, valueSet);
            tmpSize += valueCount;
         }

         ImmutableMap<Object, ImmutableSet<Object>> tmpMap;
         try {
            tmpMap = builder.build();
         } catch (IllegalArgumentException var11) {
            throw (InvalidObjectException)std::make_shared<InvalidObjectException>(var11.getMessage()).initCause(var11);
         }

         FieldSettersHolder.MAP_FIELD_SETTER.set(this, tmpMap);
         FieldSettersHolder.SIZE_FIELD_SETTER.set(this, tmpSize);
         FieldSettersHolder.EMPTY_SET_FIELD_SETTER.set(this, emptySet(valueComparator));
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
