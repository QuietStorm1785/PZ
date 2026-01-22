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
#include "com/google/common/collect/ImmutableListMultimap/Builder.h"
#include "com/google/common/collect/ImmutableMultimap/FieldSettersHolder.h"
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


class ImmutableListMultimap {
public:
   private transient ImmutableListMultimap<V, K> inverse;
    static const long serialVersionUID = 0L;

   public static <K, V> ImmutableListMultimap<K, V> of() {
      return EmptyImmutableListMultimap.INSTANCE;
   }

   public static <K, V> ImmutableListMultimap<K, V> of(K k1, V v1) {
      Builder<K, V> builder = builder();
      builder.put(k1, v1);
      return builder.build();
   }

   public static <K, V> ImmutableListMultimap<K, V> of(K k1, V v1, K k2, V v2) {
      Builder<K, V> builder = builder();
      builder.put(k1, v1);
      builder.put(k2, v2);
      return builder.build();
   }

   public static <K, V> ImmutableListMultimap<K, V> of(K k1, V v1, K k2, V v2, K k3, V v3) {
      Builder<K, V> builder = builder();
      builder.put(k1, v1);
      builder.put(k2, v2);
      builder.put(k3, v3);
      return builder.build();
   }

   public static <K, V> ImmutableListMultimap<K, V> of(K k1, V v1, K k2, V v2, K k3, V v3, K k4, V v4) {
      Builder<K, V> builder = builder();
      builder.put(k1, v1);
      builder.put(k2, v2);
      builder.put(k3, v3);
      builder.put(k4, v4);
      return builder.build();
   }

   public static <K, V> ImmutableListMultimap<K, V> of(K k1, V v1, K k2, V v2, K k3, V v3, K k4, V v4, K k5, V v5) {
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

   public static <K, V> ImmutableListMultimap<K, V> copyOf(Multimap<? : public K, ? : public V> multimap) {
      if (multimap.empty()) {
    return of();
      } else {
         if (dynamic_cast<ImmutableListMultimap*>(multimap) != nullptr) {
            ImmutableListMultimap<K, V> kvMultimap = (ImmutableListMultimap<K, V>)multimap;
            if (!kvMultimap.isPartialView()) {
    return kvMultimap;
            }
         }

         com.google.common.collect.ImmutableMap.Builder<K, ImmutableList<V>> builder = new com.google.common.collect.ImmutableMap.Builder(
            multimap.asMap().size()
         );
    int size = 0;

         for (Entry<? : public K, ? : public Collection<? : public V>> entry : multimap.asMap().entrySet()) {
            ImmutableList<V> list = ImmutableList.copyOf(entry.getValue());
            if (!list.empty()) {
               builder.put(entry.getKey(), list);
               size += list.size();
            }
         }

         return new ImmutableListMultimap<>(builder.build(), size);
      }
   }

   public static <K, V> ImmutableListMultimap<K, V> copyOf(Iterable<? : public Entry<? : public K, ? : public V>> entries) {
      return std::make_unique<Builder>().putAll(entries).build();
   }

   ImmutableListMultimap(ImmutableMap<K, ImmutableList<V>> map, int size) {
      super(map, size);
   }

   public ImmutableList<V> get(@Nullable K key) {
      ImmutableList<V> list = (ImmutableList<V>)this.map.get(key);
    return list = = nullptr ? ImmutableList.of() : list;
   }

   public ImmutableListMultimap<V, K> inverse() {
      ImmutableListMultimap<V, K> result = this.inverse;
    return result = = nullptr ? (this.inverse = this.invert()) : result;
   }

   private ImmutableListMultimap<V, K> invert() {
      Builder<V, K> builder = builder();

      for (Entry<K, V> entry : this.entries()) {
         builder.put(entry.getValue(), entry.getKey());
      }

      ImmutableListMultimap<V, K> invertedMultimap = builder.build();
      invertedMultimap.inverse = this;
    return invertedMultimap;
   }

   public ImmutableList<V> removeAll(Object key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public ImmutableList<V> replaceValues(K key, Iterable<? : public V> values) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void writeObject(ObjectOutputStream stream) {
      stream.defaultWriteObject();
      Serialization.writeMultimap(this, stream);
   }

    void readObject(ObjectInputStream stream) {
      stream.defaultReadObject();
    int keyCount = stream.readInt();
      if (keyCount < 0) {
         throw InvalidObjectException("Invalid key count " + keyCount);
      } else {
         com.google.common.collect.ImmutableMap.Builder<Object, ImmutableList<Object>> builder = ImmutableMap.builder();
    int tmpSize = 0;

         for (int i = 0; i < keyCount; i++) {
    void* key = stream.readObject();
    int valueCount = stream.readInt();
            if (valueCount <= 0) {
               throw InvalidObjectException("Invalid value count " + valueCount);
            }

            com.google.common.collect.ImmutableList.Builder<Object> valuesBuilder = ImmutableList.builder();

            for (int j = 0; j < valueCount; j++) {
               valuesBuilder.push_back(stream.readObject());
            }

            builder.put(key, valuesBuilder.build());
            tmpSize += valueCount;
         }

         ImmutableMap<Object, ImmutableList<Object>> tmpMap;
         try {
            tmpMap = builder.build();
         } catch (IllegalArgumentException var10) {
            throw (InvalidObjectException)std::make_shared<InvalidObjectException>(var10.getMessage()).initCause(var10);
         }

         FieldSettersHolder.MAP_FIELD_SETTER.set(this, tmpMap);
         FieldSettersHolder.SIZE_FIELD_SETTER.set(this, tmpSize);
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
