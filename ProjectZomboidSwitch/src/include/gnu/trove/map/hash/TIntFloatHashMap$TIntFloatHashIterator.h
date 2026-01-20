#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/impl/hash/THashPrimitiveIterator.h"
#include "gnu/trove/iterator/TIntFloatIterator.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class TIntFloatHashMap {
public:
   TIntFloatHashMap$TIntFloatHashIterator(TIntFloatHashMap var1, TIntFloatHashMap map) {
      super(map);
      this.this$0 = var1;
   }

    void advance() {
      this.moveToNextIndex();
   }

    int key() {
      return this.this$0._set[this._index];
   }

    float value() {
      return this.this$0._values[this._index];
   }

    float setValue(float val) {
    float old = this.value();
      this.this$0._values[this._index] = val;
    return old;
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
