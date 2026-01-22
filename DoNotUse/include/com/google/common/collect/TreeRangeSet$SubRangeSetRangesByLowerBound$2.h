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
   TreeRangeSet$SubRangeSetRangesByLowerBound$2(SubRangeSetRangesByLowerBound var1, Iterator var2) {
      this.this$0 = var1;
      this.val$completeRangeItr = var2;
   }

   protected Entry<Cut<C>, Range<C>> computeNext() {
      if (!this.val$completeRangeItr.hasNext()) {
         return (Entry<Cut<C>, Range<C>>)this.endOfData();
      } else {
         Range<C> nextRange = (Range<C>)this.val$completeRangeItr.next();
         if (SubRangeSetRangesByLowerBound.access$300(this.this$0).lowerBound.compareTo(nextRange.upperBound) >= 0) {
            return (Entry<Cut<C>, Range<C>>)this.endOfData();
         } else {
            nextRange = nextRange.intersection(SubRangeSetRangesByLowerBound.access$300(this.this$0));
            return SubRangeSetRangesByLowerBound.access$400(this.this$0).contains(nextRange.lowerBound)
               ? Maps.immutableEntry(nextRange.lowerBound, nextRange)
               : (Entry)this.endOfData();
         }
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
