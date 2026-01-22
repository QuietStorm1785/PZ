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

namespace gnu {
namespace trove {
namespace set {
namespace hash {


class TLongHashSet {
public:
    const TLongHash _hash;

   public TLongHashSet$TLongHashIterator(TLongHashSet var1, TLongHash hash) {
      super(hash);
      this.this$0 = var1;
      this._hash = hash;
   }

    long next() {
      this.moveToNextIndex();
      return this._hash._set[this._index];
   }
}
} // namespace hash
} // namespace set
} // namespace trove
} // namespace gnu
