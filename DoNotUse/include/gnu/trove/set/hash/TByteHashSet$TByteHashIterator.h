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

namespace gnu {
namespace trove {
namespace set {
namespace hash {


class TByteHashSet {
public:
    const TByteHash _hash;

   public TByteHashSet$TByteHashIterator(TByteHashSet var1, TByteHash hash) {
      super(hash);
      this.this$0 = var1;
      this._hash = hash;
   }

    uint8_t next() {
      this.moveToNextIndex();
      return this._hash._set[this._index];
   }
}
} // namespace hash
} // namespace set
} // namespace trove
} // namespace gnu
