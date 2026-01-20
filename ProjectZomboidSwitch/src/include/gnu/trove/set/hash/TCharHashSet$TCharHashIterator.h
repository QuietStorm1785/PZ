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

namespace gnu {
namespace trove {
namespace set {
namespace hash {


class TCharHashSet {
public:
    const TCharHash _hash;

   public TCharHashSet$TCharHashIterator(TCharHashSet var1, TCharHash hash) {
      super(hash);
      this.this$0 = var1;
      this._hash = hash;
   }

    char next() {
      this.moveToNextIndex();
      return this._hash._set[this._index];
   }
}
} // namespace hash
} // namespace set
} // namespace trove
} // namespace gnu
