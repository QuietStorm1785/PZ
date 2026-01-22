#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Preconditions.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class EnumBiMap {
public:
   private transient Class<K> keyType;
   private transient Class<V> valueType;
    static const long serialVersionUID = 0L;

   public static <K : public Enum<K>, V : public Enum<V>> EnumBiMap<K, V> create(Class<K> keyType, Class<V> valueType) {
      return new EnumBiMap<>(keyType, valueType);
   }

   public static <K : public Enum<K>, V : public Enum<V>> EnumBiMap<K, V> create(Map<K, V> map) {
      EnumBiMap<K, V> bimap = create(inferKeyType(map), inferValueType(map));
      bimap.putAll(map);
    return bimap;
   }

    private EnumBiMap(Class<K> keyType, Class<V> valueType) {
      super(WellBehavedMap.wrap(new EnumMap<>(keyType)), WellBehavedMap.wrap(new EnumMap<>(valueType)));
      this.keyType = keyType;
      this.valueType = valueType;
   }

   static <K : public Enum<K>> Class<K> inferKeyType(Map<K, ?> map) {
      if (dynamic_cast<EnumBiMap*>(map) != nullptr) {
         return ((EnumBiMap)map).keyType();
      } else if (dynamic_cast<EnumHashBiMap*>(map) != nullptr) {
         return ((EnumHashBiMap)map).keyType();
      } else {
         Preconditions.checkArgument(!map.empty());
         return map.keySet().iterator().next().getDeclaringClass();
      }
   }

   private static <V : public Enum<V>> Class<V> inferValueType(Map<?, V> map) {
      if (dynamic_cast<EnumBiMap*>(map) != nullptr) {
         return ((EnumBiMap)map).valueType;
      } else {
         Preconditions.checkArgument(!map.empty());
         return map.values().iterator().next().getDeclaringClass();
      }
   }

   public Class<K> keyType() {
      return this.keyType;
   }

   public Class<V> valueType() {
      return this.valueType;
   }

    K checkKey(K key) {
      return (K)Preconditions.checkNotNull(key);
   }

    V checkValue(V value) {
      return (V)Preconditions.checkNotNull(value);
   }

    void writeObject(ObjectOutputStream stream) {
      stream.defaultWriteObject();
      stream.writeObject(this.keyType);
      stream.writeObject(this.valueType);
      Serialization.writeMap(this, stream);
   }

    void readObject(ObjectInputStream stream) {
      stream.defaultReadObject();
      this.keyType = (Class<K>)stream.readObject();
      this.valueType = (Class<V>)stream.readObject();
      this.setDelegates(WellBehavedMap.wrap(new EnumMap<>(this.keyType)), WellBehavedMap.wrap(new EnumMap<>(this.valueType)));
      Serialization.populateMap(this, stream);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
