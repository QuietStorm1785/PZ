#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/impl/hash/THashPrimitiveIterator.h"
#include "gnu/trove/impl/hash/TIntHash.h"
#include "gnu/trove/iterator/TIntIterator.h"
#include "gnu/trove/map/hash/TIntObjectHashMap/KeyView.h"

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class TIntObjectHashMap {
public:
    const TIntHash _hash;

   public TIntObjectHashMap$KeyView$TIntHashIterator(KeyView var1, TIntHash hash) {
      super(hash);
      this.this$1 = var1;
      this._hash = hash;
   }

    int next() {
      this.moveToNextIndex();
      return this._hash._set[this._index];
   }
}
} // namespace hash
} // namespace map
} // namespace trove
} // namespace gnu
