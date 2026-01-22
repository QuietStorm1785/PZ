#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/impl/hash/THashPrimitiveIterator.h"
#include "gnu/trove/impl/hash/TShortHash.h"
#include "gnu/trove/iterator/TShortIterator.h"
#include "gnu/trove/map/hash/TShortObjectHashMap/KeyView.h"

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class TShortObjectHashMap {
public:
    const TShortHash _hash;

   public TShortObjectHashMap$KeyView$TShortHashIterator(KeyView var1, TShortHash hash) {
      super(hash);
      this.this$1 = var1;
      this._hash = hash;
   }

    short next() {
      this.moveToNextIndex();
      return this._hash._set[this._index];
   }
}
} // namespace hash
} // namespace map
} // namespace trove
} // namespace gnu
