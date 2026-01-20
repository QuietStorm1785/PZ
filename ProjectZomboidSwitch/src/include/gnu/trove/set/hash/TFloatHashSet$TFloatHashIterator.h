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

namespace gnu {
namespace trove {
namespace set {
namespace hash {


class TFloatHashSet {
public:
    const TFloatHash _hash;

   public TFloatHashSet$TFloatHashIterator(TFloatHashSet var1, TFloatHash hash) {
      super(hash);
      this.this$0 = var1;
      this._hash = hash;
   }

    float next() {
      this.moveToNextIndex();
      return this._hash._set[this._index];
   }
}
} // namespace hash
} // namespace set
} // namespace trove
} // namespace gnu
