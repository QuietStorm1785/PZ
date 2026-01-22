#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/TreeRangeSet/ComplementRangesByLowerBound.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class TreeRangeSet {
public:
   Cut<C> nextComplementRangeUpperBound;

   TreeRangeSet$ComplementRangesByLowerBound$2(ComplementRangesByLowerBound var1, Cut var2, PeekingIterator var3) {
      this.this$0 = var1;
      this.val$firstComplementRangeUpperBound = var2;
      this.val$positiveItr = var3;
      this.nextComplementRangeUpperBound = this.val$firstComplementRangeUpperBound;
   }

   protected Entry<Cut<C>, Range<C>> computeNext() {
      if (this.nextComplementRangeUpperBound == Cut.belowAll()) {
         return (Entry<Cut<C>, Range<C>>)this.endOfData();
      } else {
         if (this.val$positiveItr.hasNext()) {
            Range<C> positiveRange = (Range<C>)this.val$positiveItr.next();
            Range<C> negativeRange = Range.create(positiveRange.upperBound, this.nextComplementRangeUpperBound);
            this.nextComplementRangeUpperBound = positiveRange.lowerBound;
            if (ComplementRangesByLowerBound.access$100(this.this$0).lowerBound.isLessThan(negativeRange.lowerBound)) {
               return Maps.immutableEntry(negativeRange.lowerBound, negativeRange);
            }
         } else if (ComplementRangesByLowerBound.access$100(this.this$0).lowerBound.isLessThan(Cut.belowAll())) {
            Range<C> negativeRange = Range.create(Cut.belowAll(), this.nextComplementRangeUpperBound);
            this.nextComplementRangeUpperBound = Cut.belowAll();
            return Maps.immutableEntry(Cut.belowAll(), negativeRange);
         }

         return (Entry<Cut<C>, Range<C>>)this.endOfData();
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
