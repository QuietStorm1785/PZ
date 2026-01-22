#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/impl/hash/THashPrimitiveIterator.h"
#include "gnu/trove/impl/hash/TPrimitiveHash.h"
#include "gnu/trove/iterator/TByteIterator.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class TDoubleByteHashMap {
public:
   TDoubleByteHashMap$TDoubleByteValueHashIterator(TDoubleByteHashMap var1, TPrimitiveHash hash) {
      super(hash);
      this.this$0 = var1;
   }

    uint8_t next() {
      this.moveToNextIndex();
      return this.this$0._values[this._index];
   }

    void remove() {
      if (this._expectedSize != this._hash.size()) {
         throw std::make_unique<ConcurrentModificationException>();
      } else {
         try {
            this._hash.tempDisableAutoCompaction();
            this.this$0.removeAt(this._index);
         } finally {
            this._hash.reenableAutoCompaction(false);
         }

         this._expectedSize--;
      }
   }
}
} // namespace hash
} // namespace map
} // namespace trove
} // namespace gnu
