#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/TreeRangeSet/SubRangeSetRangesByLowerBound.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class TreeRangeSet {
public:
   TreeRangeSet$SubRangeSetRangesByLowerBound$1(SubRangeSetRangesByLowerBound var1, Iterator var2, Cut var3) {
      this.this$0 = var1;
      this.val$completeRangeItr = var2;
      this.val$upperBoundOnLowerBounds = var3;
   }

   protected Entry<Cut<C>, Range<C>> computeNext() {
      if (!this.val$completeRangeItr.hasNext()) {
         return (Entry<Cut<C>, Range<C>>)this.endOfData();
      } else {
         Range<C> nextRange = (Range<C>)this.val$completeRangeItr.next();
         if (this.val$upperBoundOnLowerBounds.isLessThan(nextRange.lowerBound)) {
            return (Entry<Cut<C>, Range<C>>)this.endOfData();
         } else {
            nextRange = nextRange.intersection(SubRangeSetRangesByLowerBound.access$300(this.this$0));
            return Maps.immutableEntry(nextRange.lowerBound, nextRange);
         }
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
