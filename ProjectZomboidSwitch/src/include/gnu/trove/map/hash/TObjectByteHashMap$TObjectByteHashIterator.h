#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/iterator/TObjectByteIterator.h"
#include "gnu/trove/iterator/hash/TObjectHashIterator.h"

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class TObjectByteHashMap {
public:
   private const TObjectByteHashMap<K> _map;

   public TObjectByteHashMap$TObjectByteHashIterator(TObjectByteHashMap<K> var1, TObjectByteHashMap map) {
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

    uint8_t value() {
      return this._map._values[this._index];
   }

    uint8_t setValue(uint8_t val) {
    uint8_t old = this.value();
      this._map._values[this._index] = val;
    return old;
   }
}
} // namespace hash
} // namespace map
} // namespace trove
} // namespace gnu
