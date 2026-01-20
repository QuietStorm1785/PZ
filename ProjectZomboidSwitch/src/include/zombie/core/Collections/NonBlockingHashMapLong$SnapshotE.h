#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Collections/NonBlockingHashMapLong/NBHMLEntry.h"
#include "zombie/core/Collections/NonBlockingHashMapLong/SnapshotV.h"
#include <algorithm>
#include <iterator>

namespace zombie {
namespace core {
namespace Collections {


class NonBlockingHashMapLong {
public:
   const NonBlockingHashMapLong<TypeV>.SnapshotV _ss;

   public NonBlockingHashMapLong$SnapshotE(NonBlockingHashMapLong var1) {
      this.this$0 = var1;
      this._ss = std::make_shared<SnapshotV>(var1);
   }

    void remove() {
      this._ss.remove();
   }

   public Entry<int64_t, TypeV> next() {
      this._ss.next();
      return std::make_shared<NBHMLEntry>(this.this$0, this._ss._prevK, this._ss._prevV);
   }

    bool hasNext() {
      return this._ss.hasNext();
   }
}
} // namespace Collections
} // namespace core
} // namespace zombie
