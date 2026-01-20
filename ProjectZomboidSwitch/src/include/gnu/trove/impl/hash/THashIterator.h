#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/iterator/TIterator.h"
#include <algorithm>
#include <iterator>

namespace gnu {
namespace trove {
namespace impl {
namespace hash {


class THashIterator {
public:
   private const TObjectHash<V> _object_hash;
    const THash _hash;
    int _expectedSize;
    int _index;

    protected THashIterator(TObjectHash<V> hash) {
      this._hash = hash;
      this._expectedSize = this._hash.size();
      this._index = this._hash.capacity();
      this._object_hash = hash;
   }

    V next() {
      this.moveToNextIndex();
      return this.objectAtIndex(this._index);
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

    int nextIndex() {
      if (this._expectedSize != this._hash.size()) {
         throw std::make_unique<ConcurrentModificationException>();
      } else {
         Object[] set = this._object_hash._set;
    int i = this._index;

         while (i-- > 0 && (set[i] == TObjectHash.FREE || set[i] == TObjectHash.REMOVED)) {
         }

    return i;
      }
   }

   protected abstract V objectAtIndex(int var1);
}
} // namespace hash
} // namespace impl
} // namespace trove
} // namespace gnu
