#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/impl/hash/TCharHash.h"
#include "gnu/trove/impl/hash/THashPrimitiveIterator.h"
#include "gnu/trove/iterator/TCharIterator.h"
#include "gnu/trove/map/hash/TCharObjectHashMap/KeyView.h"

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class TCharObjectHashMap {
public:
    const TCharHash _hash;

   public TCharObjectHashMap$KeyView$TCharHashIterator(KeyView var1, TCharHash hash) {
      super(hash);
      this.this$1 = var1;
      this._hash = hash;
   }

    char next() {
      this.moveToNextIndex();
      return this._hash._set[this._index];
   }
}
} // namespace hash
} // namespace map
} // namespace trove
} // namespace gnu
