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

namespace gnu {
namespace trove {
namespace set {
namespace hash {


class TIntHashSet {
public:
    const TIntHash _hash;

   public TIntHashSet$TIntHashIterator(TIntHashSet var1, TIntHash hash) {
      super(hash);
      this.this$0 = var1;
      this._hash = hash;
   }

    int next() {
      this.moveToNextIndex();
      return this._hash._set[this._index];
   }
}
} // namespace hash
} // namespace set
} // namespace trove
} // namespace gnu
