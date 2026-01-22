#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/impl/hash/THashPrimitiveIterator.h"
#include "gnu/trove/iterator/TIntObjectIterator.h"

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class TIntObjectHashMap {
public:
   private const TIntObjectHashMap<V> _map;

   public TIntObjectHashMap$TIntObjectHashIterator(TIntObjectHashMap<V> var1, TIntObjectHashMap map) {
      super(map);
      this.this$0 = var1;
      this._map = map;
   }

    void advance() {
      this.moveToNextIndex();
   }

    int key() {
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
