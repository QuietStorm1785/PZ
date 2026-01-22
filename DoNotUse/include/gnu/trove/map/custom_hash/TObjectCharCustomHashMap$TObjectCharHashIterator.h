#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/iterator/TObjectCharIterator.h"
#include "gnu/trove/iterator/hash/TObjectHashIterator.h"

namespace gnu {
namespace trove {
namespace map {
namespace custom_hash {


class TObjectCharCustomHashMap {
public:
   private const TObjectCharCustomHashMap<K> _map;

   public TObjectCharCustomHashMap$TObjectCharHashIterator(TObjectCharCustomHashMap<K> var1, TObjectCharCustomHashMap map) {
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

    char value() {
      return this._map._values[this._index];
   }

    char setValue(char val) {
    char old = this.value();
      this._map._values[this._index] = val;
    return old;
   }
}
} // namespace custom_hash
} // namespace map
} // namespace trove
} // namespace gnu
