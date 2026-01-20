#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/impl/hash/THash.h"
#include "gnu/trove/impl/hash/TObjectHash.h"
#include "gnu/trove/iterator/TLongIterator.h"
#include "gnu/trove/map/hash/TObjectLongHashMap/TLongValueCollection.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class TObjectLongHashMap {
public:
    THash _hash;
    int _expectedSize;
    int _index;

   TObjectLongHashMap$TLongValueCollection$TObjectLongValueHashIterator(TLongValueCollection var1) {
      this.this$1 = var1;
      this._hash = this.this$1.this$0;
      this._expectedSize = this._hash.size();
      this._index = this._hash.capacity();
   }

    bool hasNext() {
      return this.nextIndex() >= 0;
   }

    long next() {
      this.moveToNextIndex();
      return this.this$1.this$0._values[this._index];
   }

    void remove() {
      if (this._expectedSize != this._hash.size()) {
         throw std::make_unique<ConcurrentModificationException>();
      } else {
         try {
            this._hash.tempDisableAutoCompaction();
            this.this$1.this$0.removeAt(this._index);
         } finally {
            this._hash.reenableAutoCompaction(false);
         }

         this._expectedSize--;
      }
   }

    void moveToNextIndex() {
      if ((this._index = this.nextIndex()) < 0) {
         throw std::make_unique<NoSuchElementException>();
      }
   }

    int nextIndex() {
      if (this._expectedSize != this._hash.size()) {
         throw std::make_unique<ConcurrentModificationException>();
      } else {
         Object[] set = this.this$1.this$0._set;
    int i = this._index;

         while (i-- > 0 && (set[i] == TObjectHash.FREE || set[i] == TObjectHash.REMOVED)) {
         }

    return i;
      }
   }
}
} // namespace hash
} // namespace map
} // namespace trove
} // namespace gnu
