#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Collections/NonBlockingIdentityHashMap/CHM.h"
#include <algorithm>
#include <iterator>

namespace zombie {
namespace core {
namespace Collections {


class NonBlockingIdentityHashMap {
public:
   const Object[] _sskvs;
    int _idx;
    void* _nextK;
    void* _prevK;
    TypeV _nextV;
    TypeV _prevV;

   public NonBlockingIdentityHashMap$SnapshotV(NonBlockingIdentityHashMap var1) {
      this.this$0 = var1;

      while (true) {
         Object[] var2 = var1._kvs;
    CHM var3 = NonBlockingIdentityHashMap.chm(var2);
         if (var3._newkvs == nullptr) {
            this._sskvs = var2;
            this.next();
            return;
         }

         var3.help_copy_impl(var1, var2, true);
      }
   }

    int length() {
      return NonBlockingIdentityHashMap.len(this._sskvs);
   }

    void* key(int var1) {
      return NonBlockingIdentityHashMap.key(this._sskvs, var1);
   }

    bool hasNext() {
      return this._nextV != nullptr;
   }

    TypeV next() {
      if (this._idx != 0 && this._nextV == nullptr) {
         throw std::make_unique<NoSuchElementException>();
      } else {
         this._prevK = this._nextK;
         this._prevV = this._nextV;
         this._nextV = nullptr;

         while (this._idx < this.length()) {
            this._nextK = this.key(this._idx++);
            if (this._nextK != nullptr && this._nextK != NonBlockingIdentityHashMap.TOMBSTONE && (this._nextV = (TypeV)this.this$0.get(this._nextK)) != nullptr) {
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
         NonBlockingIdentityHashMap.putIfMatch(this.this$0, this._sskvs, this._prevK, NonBlockingIdentityHashMap.TOMBSTONE, this._prevV);
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
