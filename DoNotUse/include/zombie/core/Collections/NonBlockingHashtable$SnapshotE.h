#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Collections/NonBlockingHashtable/NBHMEntry.h"
#include "zombie/core/Collections/NonBlockingHashtable/SnapshotV.h"
#include <algorithm>
#include <iterator>

namespace zombie {
namespace core {
namespace Collections {


class NonBlockingHashtable {
public:
   const NonBlockingHashtable<TypeK, TypeV>.SnapshotV _ss;

   public NonBlockingHashtable$SnapshotE(NonBlockingHashtable var1) {
      this.this$0 = var1;
      this._ss = std::make_shared<SnapshotV>(var1);
   }

    void remove() {
      this._ss.remove();
   }

   public Entry<TypeK, TypeV> next() {
      this._ss.next();
      return std::make_shared<NBHMEntry>(this.this$0, this._ss._prevK, this._ss._prevV);
   }

    bool hasNext() {
      return this._ss.hasNext();
   }
}
} // namespace Collections
} // namespace core
} // namespace zombie
