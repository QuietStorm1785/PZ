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
namespace custom_hash {


class TObjectIntCustomHashMap {
public:
   private const TObjectIntCustomHashMap<K> _map;

   public TObjectIntCustomHashMap$TObjectIntHashIterator(TObjectIntCustomHashMap<K> var1, TObjectIntCustomHashMap map) {
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
} // namespace custom_hash
} // namespace map
} // namespace trove
} // namespace gnu
