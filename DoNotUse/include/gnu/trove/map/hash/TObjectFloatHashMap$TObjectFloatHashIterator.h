#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/iterator/TObjectFloatIterator.h"
#include "gnu/trove/iterator/hash/TObjectHashIterator.h"

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class TObjectFloatHashMap {
public:
   private const TObjectFloatHashMap<K> _map;

   public TObjectFloatHashMap$TObjectFloatHashIterator(TObjectFloatHashMap<K> var1, TObjectFloatHashMap map) {
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

    float value() {
      return this._map._values[this._index];
   }

    float setValue(float val) {
    float old = this.value();
      this._map._values[this._index] = val;
    return old;
   }
}
} // namespace hash
} // namespace map
} // namespace trove
} // namespace gnu
