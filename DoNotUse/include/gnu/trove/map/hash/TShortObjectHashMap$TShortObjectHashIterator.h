#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/impl/hash/THashPrimitiveIterator.h"
#include "gnu/trove/iterator/TShortObjectIterator.h"

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class TShortObjectHashMap {
public:
   private const TShortObjectHashMap<V> _map;

   public TShortObjectHashMap$TShortObjectHashIterator(TShortObjectHashMap<V> var1, TShortObjectHashMap map) {
      super(map);
      this.this$0 = var1;
      this._map = map;
   }

    void advance() {
      this.moveToNextIndex();
   }

    short key() {
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
