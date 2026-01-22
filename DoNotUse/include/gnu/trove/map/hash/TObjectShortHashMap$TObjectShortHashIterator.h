#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/iterator/TObjectShortIterator.h"
#include "gnu/trove/iterator/hash/TObjectHashIterator.h"

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class TObjectShortHashMap {
public:
   private const TObjectShortHashMap<K> _map;

   public TObjectShortHashMap$TObjectShortHashIterator(TObjectShortHashMap<K> var1, TObjectShortHashMap map) {
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

    short value() {
      return this._map._values[this._index];
   }

    short setValue(short val) {
    short old = this.value();
      this._map._values[this._index] = val;
    return old;
   }
}
} // namespace hash
} // namespace map
} // namespace trove
} // namespace gnu
