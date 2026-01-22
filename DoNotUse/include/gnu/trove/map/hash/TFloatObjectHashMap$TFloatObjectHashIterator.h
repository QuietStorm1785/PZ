#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/impl/hash/THashPrimitiveIterator.h"
#include "gnu/trove/iterator/TFloatObjectIterator.h"

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class TFloatObjectHashMap {
public:
   private const TFloatObjectHashMap<V> _map;

   public TFloatObjectHashMap$TFloatObjectHashIterator(TFloatObjectHashMap<V> var1, TFloatObjectHashMap map) {
      super(map);
      this.this$0 = var1;
      this._map = map;
   }

    void advance() {
      this.moveToNextIndex();
   }

    float key() {
      return this._map._set[this._index];
   }

    V value() {
      return (V)this._map._values[this._index];
   }

    V setValue(V val) {
    V old = this.value();
      this._map._values[this._index] = val;
    return old;
   }
}
} // namespace hash
} // namespace map
} // namespace trove
} // namespace gnu
