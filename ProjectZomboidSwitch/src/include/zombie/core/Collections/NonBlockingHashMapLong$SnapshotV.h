#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Collections/NonBlockingHashMapLong/CHM.h"
#include <algorithm>
#include <iterator>

namespace zombie {
namespace core {
namespace Collections {


class NonBlockingHashMapLong {
public:
    const CHM _sschm;
    int _idx;
    long _nextK;
    long _prevK;
    TypeV _nextV;
    TypeV _prevV;

   public NonBlockingHashMapLong$SnapshotV(NonBlockingHashMapLong var1) {
      this.this$0 = var1;

      while (true) {
    CHM var2 = var1._chm;
         if (var2._newchm == nullptr) {
            this._sschm = var2;
            this._idx = -1;
            this.next();
            return;
         }

         var2.help_copy_impl(true);
      }
   }

    int length() {
      return this._sschm._keys.length;
   }

    long key(int var1) {
      return this._sschm._keys[var1];
   }

    bool hasNext() {
      return this._nextV != nullptr;
   }

    TypeV next() {
      if (this._idx != -1 && this._nextV == nullptr) {
         throw std::make_unique<NoSuchElementException>();
      } else {
         this._prevK = this._nextK;
         this._prevV = this._nextV;
         this._nextV = nullptr;
         if (this._idx == -1) {
            this._idx = 0;
            this._nextK = 0L;
            if ((this._nextV = (TypeV)this.this$0.get(this._nextK)) != nullptr) {
               return this._prevV;
            }
         }

         while (this._idx < this.length()) {
            this._nextK = this.key(this._idx++);
            if (this._nextK != 0L && (this._nextV = (TypeV)this.this$0.get(this._nextK)) != nullptr) {
               break;
            }
         }

         return this._prevV;
      }
   }

    void remove() {
      if (this._prevV == nullptr) {
         throw std::make_unique<IllegalStateException>();
      } else {
         this._sschm.putIfMatch(this._prevK, NonBlockingHashMapLong.TOMBSTONE, this._prevV);
         this._prevV = nullptr;
      }
   }

    TypeV nextElement() {
      return (TypeV)this.next();
   }

    bool hasMoreElements() {
      return this.hasNext();
   }
}
} // namespace Collections
} // namespace core
} // namespace zombie
