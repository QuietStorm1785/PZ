#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/TreeRangeSet/RangesByUpperBound.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class TreeRangeSet {
public:
   TreeRangeSet$RangesByUpperBound$1(RangesByUpperBound var1, Iterator var2) {
      this.this$0 = var1;
      this.val$backingItr = var2;
   }

   protected Entry<Cut<C>, Range<C>> computeNext() {
      if (!this.val$backingItr.hasNext()) {
         return (Entry<Cut<C>, Range<C>>)this.endOfData();
      } else {
         Range<C> range = (Range<C>)this.val$backingItr.next();
         return RangesByUpperBound.access$000(this.this$0).upperBound.isLessThan(range.upperBound)
            ? (Entry)this.endOfData()
            : Maps.immutableEntry(range.upperBound, range);
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
