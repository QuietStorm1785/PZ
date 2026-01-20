#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/impl/hash/TObjectHash.h"
#include "gnu/trove/iterator/TIntIterator.h"
#include "gnu/trove/iterator/hash/TObjectHashIterator.h"

namespace gnu {
namespace trove {
namespace set {
namespace hash {


class TLinkedHashSet {
public:
    TIntIterator localIterator;
    int lastIndex;

   TLinkedHashSet$2(TLinkedHashSet var1, TObjectHash x0) {
      super(x0);
      this.this$0 = var1;
      this.localIterator = this.this$0.order.iterator();
   }

    E next() {
      this.lastIndex = this.localIterator.next();
      return (E)this.objectAtIndex(this.lastIndex);
   }

    bool hasNext() {
      return this.localIterator.hasNext();
   }

    void remove() {
      this.localIterator.remove();

      try {
         this._hash.tempDisableAutoCompaction();
         this.this$0.removeAt(this.lastIndex);
      } finally {
         this._hash.reenableAutoCompaction(false);
      }
   }
}
} // namespace hash
} // namespace set
} // namespace trove
} // namespace gnu
