#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/impl/hash/TFloatHash.h"
#include "gnu/trove/impl/hash/THashPrimitiveIterator.h"
#include "gnu/trove/iterator/TFloatIterator.h"
#include "gnu/trove/map/hash/TFloatObjectHashMap/KeyView.h"

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class TFloatObjectHashMap {
public:
    const TFloatHash _hash;

   public TFloatObjectHashMap$KeyView$TFloatHashIterator(KeyView var1, TFloatHash hash) {
      super(hash);
      this.this$1 = var1;
      this._hash = hash;
   }

    float next() {
      this.moveToNextIndex();
      return this._hash._set[this._index];
   }
}
} // namespace hash
} // namespace map
} // namespace trove
} // namespace gnu
