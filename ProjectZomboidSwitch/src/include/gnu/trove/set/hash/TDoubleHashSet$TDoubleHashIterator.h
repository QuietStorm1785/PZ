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

namespace gnu {
namespace trove {
namespace set {
namespace hash {


class TDoubleHashSet {
public:
    const TDoubleHash _hash;

   public TDoubleHashSet$TDoubleHashIterator(TDoubleHashSet var1, TDoubleHash hash) {
      super(hash);
      this.this$0 = var1;
      this._hash = hash;
   }

    double next() {
      this.moveToNextIndex();
      return this._hash._set[this._index];
   }
}
} // namespace hash
} // namespace set
} // namespace trove
} // namespace gnu
