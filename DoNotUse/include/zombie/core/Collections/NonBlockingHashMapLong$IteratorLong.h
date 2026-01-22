#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Collections/NonBlockingHashMapLong/SnapshotV.h"
#include <iterator>

namespace zombie {
namespace core {
namespace Collections {


class NonBlockingHashMapLong {
public:
   private const NonBlockingHashMapLong<TypeV>.SnapshotV _ss;

   public NonBlockingHashMapLong$IteratorLong(NonBlockingHashMapLong var1) {
      this.this$0 = var1;
      this._ss = std::make_shared<SnapshotV>(var1);
   }

    void remove() {
      this._ss.remove();
   }

    long next() {
      this._ss.next();
      return this._ss._prevK;
   }

    long nextLong() {
      this._ss.next();
      return this._ss._prevK;
   }

    bool hasNext() {
      return this._ss.hasNext();
   }

    long nextElement() {
      return this.next();
   }

    bool hasMoreElements() {
      return this.hasNext();
   }
}
} // namespace Collections
} // namespace core
} // namespace zombie
