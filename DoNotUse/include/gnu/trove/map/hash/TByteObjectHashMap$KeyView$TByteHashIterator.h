#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/impl/hash/TByteHash.h"
#include "gnu/trove/impl/hash/THashPrimitiveIterator.h"
#include "gnu/trove/iterator/TByteIterator.h"
#include "gnu/trove/map/hash/TByteObjectHashMap/KeyView.h"

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class TByteObjectHashMap {
public:
    const TByteHash _hash;

   public TByteObjectHashMap$KeyView$TByteHashIterator(KeyView var1, TByteHash hash) {
      super(hash);
      this.this$1 = var1;
      this._hash = hash;
   }

    uint8_t next() {
      this.moveToNextIndex();
      return this._hash._set[this._index];
   }
}
} // namespace hash
} // namespace map
} // namespace trove
} // namespace gnu
