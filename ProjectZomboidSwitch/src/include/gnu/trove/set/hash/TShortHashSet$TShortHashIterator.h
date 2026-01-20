#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/impl/hash/THashPrimitiveIterator.h"
#include "gnu/trove/impl/hash/TShortHash.h"
#include "gnu/trove/iterator/TShortIterator.h"

namespace gnu {
namespace trove {
namespace set {
namespace hash {


class TShortHashSet {
public:
    const TShortHash _hash;

   public TShortHashSet$TShortHashIterator(TShortHashSet var1, TShortHash hash) {
      super(hash);
      this.this$0 = var1;
      this._hash = hash;
   }

    short next() {
      this.moveToNextIndex();
      return this._hash._set[this._index];
   }
}
} // namespace hash
} // namespace set
} // namespace trove
} // namespace gnu
