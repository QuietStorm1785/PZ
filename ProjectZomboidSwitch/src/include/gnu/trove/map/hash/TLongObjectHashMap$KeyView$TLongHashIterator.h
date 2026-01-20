#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/impl/hash/THashPrimitiveIterator.h"
#include "gnu/trove/impl/hash/TLongHash.h"
#include "gnu/trove/iterator/TLongIterator.h"
#include "gnu/trove/map/hash/TLongObjectHashMap/KeyView.h"

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class TLongObjectHashMap {
public:
    const TLongHash _hash;

   public TLongObjectHashMap$KeyView$TLongHashIterator(KeyView var1, TLongHash hash) {
      super(hash);
      this.this$1 = var1;
      this._hash = hash;
   }

    long next() {
      this.moveToNextIndex();
      return this._hash._set[this._index];
   }
}
} // namespace hash
} // namespace map
} // namespace trove
} // namespace gnu
