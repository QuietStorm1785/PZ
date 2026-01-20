#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Equivalence.h"
#include "com/google/common/collect/MapMakerInternalMap/AbstractSerializationProxy.h"
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

   MapMakerInternalMap$SerializationProxy(
      Strength keyStrength,
      Strength valueStrength,
      Equivalence<Object> keyEquivalence,
      Equivalence<Object> valueEquivalence,
      int concurrencyLevel,
      ConcurrentMap<K, V> delegate
   ) {
      super(keyStrength, valueStrength, keyEquivalence, valueEquivalence, concurrencyLevel, delegate);
   }

    void writeObject(ObjectOutputStream out) {
      out.defaultWriteObject();
      this.writeMapTo(out);
   }

    void readObject(ObjectInputStream in) {
      in.defaultReadObject();
    MapMaker mapMaker = this.readMapMaker(in);
      this.delegate = mapMaker.makeMap();
      this.readEntries(in);
   }

    void* readResolve() {
      return this.delegate;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
