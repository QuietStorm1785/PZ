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
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class EnumHashBiMap {
public:
   private transient Class<K> keyType;
    static const long serialVersionUID = 0L;

   public static <K : public Enum<K>, V> EnumHashBiMap<K, V> create(Class<K> keyType) {
      return new EnumHashBiMap<>(keyType);
   }

   public static <K : public Enum<K>, V> EnumHashBiMap<K, V> create(Map<K, ? : public V> map) {
      EnumHashBiMap<K, V> bimap = create(EnumBiMap.inferKeyType(map));
      bimap.putAll(map);
    return bimap;
   }

    private EnumHashBiMap(Class<K> keyType) {
      super(WellBehavedMap.wrap(new EnumMap<>(keyType)), Maps.newHashMapWithExpectedSize(((Enum[])keyType.getEnumConstants()).length));
      this.keyType = keyType;
   }

    K checkKey(K key) {
      return (K)Preconditions.checkNotNull(key);
   }

    V put(K key, @Nullable V) {
      return (V)super.put(key, value);
   }

    V forcePut(K key, @Nullable V) {
      return (V)super.forcePut(key, value);
   }

   public Class<K> keyType() {
      return this.keyType;
   }

    void writeObject(ObjectOutputStream stream) {
      stream.defaultWriteObject();
      stream.writeObject(this.keyType);
      Serialization.writeMap(this, stream);
   }

    void readObject(ObjectInputStream stream) {
      stream.defaultReadObject();
      this.keyType = (Class<K>)stream.readObject();
      this.setDelegates(WellBehavedMap.wrap(new EnumMap<>(this.keyType)), new std::unordered_map(((Enum[])this.keyType.getEnumConstants()).length * 3 / 2));
      Serialization.populateMap(this, stream);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
