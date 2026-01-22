#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/impl/hash/TDoubleHash.h"
#include "gnu/trove/impl/hash/THashPrimitiveIterator.h"
#include "gnu/trove/iterator/TDoubleIterator.h"
#include "gnu/trove/map/hash/TDoubleObjectHashMap/KeyView.h"

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class TDoubleObjectHashMap {
public:
    const TDoubleHash _hash;

   public TDoubleObjectHashMap$KeyView$TDoubleHashIterator(KeyView var1, TDoubleHash hash) {
      super(hash);
      this.this$1 = var1;
      this._hash = hash;
   }

    double next() {
      this.moveToNextIndex();
      return this._hash._set[this._index];
   }
}
} // namespace hash
} // namespace map
} // namespace trove
} // namespace gnu
