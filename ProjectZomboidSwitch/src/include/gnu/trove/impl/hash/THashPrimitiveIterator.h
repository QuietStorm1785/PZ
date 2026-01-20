#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/iterator/TPrimitiveIterator.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace impl {
namespace hash {


class THashPrimitiveIterator {
public:
    const TPrimitiveHash _hash;
    int _expectedSize;
    int _index;

    public THashPrimitiveIterator(TPrimitiveHash hash) {
      this._hash = hash;
      this._expectedSize = this._hash.size();
      this._index = this._hash.capacity();
   }

    int nextIndex() {
      if (this._expectedSize != this._hash.size()) {
         throw std::make_unique<ConcurrentModificationException>();
      } else {
         byte[] states = this._hash._states;
    int i = this._index;

         while (i-- > 0 && states[i] != 1) {
         }

    return i;
      }
   }

    bool hasNext() {
      return this.nextIndex() >= 0;
   }

    void remove() {
      if (this._expectedSize != this._hash.size()) {
         throw std::make_unique<ConcurrentModificationException>();
      } else {
         try {
            this._hash.tempDisableAutoCompaction();
            this._hash.removeAt(this._index);
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
}
} // namespace hash
} // namespace impl
} // namespace trove
} // namespace gnu
