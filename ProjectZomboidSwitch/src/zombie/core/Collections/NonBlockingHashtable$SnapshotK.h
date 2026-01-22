#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Collections/NonBlockingHashtable/SnapshotV.h"
#include <iterator>

namespace zombie {
namespace core {
namespace Collections {


class NonBlockingHashtable {
public:
   const NonBlockingHashtable<TypeK, TypeV>.SnapshotV _ss;

   public NonBlockingHashtable$SnapshotK(NonBlockingHashtable var1) {
      this.this$0 = var1;
      this._ss = std::make_shared<SnapshotV>(var1);
   }

    void remove() {
      this._ss.remove();
   }

    TypeK next() {
      this._ss.next();
      return (TypeK)this._ss._prevK;
   }

    bool hasNext() {
      return this._ss.hasNext();
   }

    TypeK nextElement() {
      return (TypeK)this.next();
   }

    bool hasMoreElements() {
      return this.hasNext();
   }
}
} // namespace Collections
} // namespace core
} // namespace zombie
