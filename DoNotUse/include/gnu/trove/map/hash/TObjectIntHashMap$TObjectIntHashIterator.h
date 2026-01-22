#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/iterator/TObjectIntIterator.h"
#include "gnu/trove/iterator/hash/TObjectHashIterator.h"

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class TObjectIntHashMap {
public:
   private const TObjectIntHashMap<K> _map;

   public TObjectIntHashMap$TObjectIntHashIterator(TObjectIntHashMap<K> var1, TObjectIntHashMap map) {
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

    int value() {
      return this._map._values[this._index];
   }

    int setValue(int val) {
    int old = this.value();
      this._map._values[this._index] = val;
    return old;
   }
}
} // namespace hash
} // namespace map
} // namespace trove
} // namespace gnu
