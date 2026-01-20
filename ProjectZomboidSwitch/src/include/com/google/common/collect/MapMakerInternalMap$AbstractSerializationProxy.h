#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Equivalence.h"
#include "com/google/common/collect/MapMakerInternalMap/Strength.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class MapMakerInternalMap {
public:
    static const long serialVersionUID = 3L;
    const Strength keyStrength;
    const Strength valueStrength;
   const Equivalence<Object> keyEquivalence;
   const Equivalence<Object> valueEquivalence;
    const int concurrencyLevel;
   transient ConcurrentMap<K, V> delegate;

   MapMakerInternalMap$AbstractSerializationProxy(
      Strength keyStrength,
      Strength valueStrength,
      Equivalence<Object> keyEquivalence,
      Equivalence<Object> valueEquivalence,
      int concurrencyLevel,
      ConcurrentMap<K, V> delegate
   ) {
      this.keyStrength = keyStrength;
      this.valueStrength = valueStrength;
      this.keyEquivalence = keyEquivalence;
      this.valueEquivalence = valueEquivalence;
      this.concurrencyLevel = concurrencyLevel;
      this.delegate = delegate;
   }

   protected ConcurrentMap<K, V> delegate() {
      return this.delegate;
   }

    void writeMapTo(ObjectOutputStream out) {
      out.writeInt(this.delegate.size());

      for (Entry<K, V> entry : this.delegate.entrySet()) {
         out.writeObject(entry.getKey());
         out.writeObject(entry.getValue());
      }

      out.writeObject(nullptr);
   }

    MapMaker readMapMaker(ObjectInputStream in) {
    int size = in.readInt();
      return std::make_unique<MapMaker>()
         .initialCapacity(size)
         .setKeyStrength(this.keyStrength)
         .setValueStrength(this.valueStrength)
         .keyEquivalence(this.keyEquivalence)
         .concurrencyLevel(this.concurrencyLevel);
   }

    void readEntries(ObjectInputStream in) {
      while (true) {
    K key = (K)in.readObject();
         if (key == nullptr) {
            return;
         }

    V value = (V)in.readObject();
         this.delegate.put(key, value);
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
