#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/impl/hash/THashPrimitiveIterator.h"
#include "gnu/trove/map/hash/TCharObjectHashMap/ValueView.h"
#include <iterator>

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class TCharObjectHashMap {
public:
    const TCharObjectHashMap _map;

   public TCharObjectHashMap$ValueView$TCharObjectValueHashIterator(ValueView var1, TCharObjectHashMap map) {
      super(map);
      this.this$1 = var1;
      this._map = map;
   }

    V objectAtIndex(int index) {
      byte[] states = this.this$1.this$0._states;
    void* value = this._map._values[index];
      return (V)(states[index] != 1 ? nullptr : value);
   }

    V next() {
      this.moveToNextIndex();
      return (V)this._map._values[this._index];
   }
}
} // namespace hash
} // namespace map
} // namespace trove
} // namespace gnu
