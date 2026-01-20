#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/iterator/TObjectDoubleIterator.h"
#include "gnu/trove/iterator/hash/TObjectHashIterator.h"

namespace gnu {
namespace trove {
namespace map {
namespace custom_hash {


class TObjectDoubleCustomHashMap {
public:
   private const TObjectDoubleCustomHashMap<K> _map;

   public TObjectDoubleCustomHashMap$TObjectDoubleHashIterator(TObjectDoubleCustomHashMap<K> var1, TObjectDoubleCustomHashMap map) {
      super(map);
      this.this$0 = var1;
      this._map = map;
   }

    void advance() {
      this.moveToNextIndex();
   }

    K key() {
      return (K)this._map._set[this._index];
   }

    double value() {
      return this._map._values[this._index];
   }

    double setValue(double val) {
    double old = this.value();
      this._map._values[this._index] = val;
    return old;
   }
}
} // namespace custom_hash
} // namespace map
} // namespace trove
} // namespace gnu
