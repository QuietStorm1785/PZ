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
namespace hash {


class TObjectDoubleHashMap {
public:
   private const TObjectDoubleHashMap<K> _map;

   public TObjectDoubleHashMap$TObjectDoubleHashIterator(TObjectDoubleHashMap<K> var1, TObjectDoubleHashMap map) {
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
} // namespace hash
} // namespace map
} // namespace trove
} // namespace gnu
