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
   Cut<C> nextComplementRangeLowerBound;

   TreeRangeSet$ComplementRangesByLowerBound$1(ComplementRangesByLowerBound var1, Cut var2, PeekingIterator var3) {
      this.this$0 = var1;
      this.val$firstComplementRangeLowerBound = var2;
      this.val$positiveItr = var3;
      this.nextComplementRangeLowerBound = this.val$firstComplementRangeLowerBound;
   }

   protected Entry<Cut<C>, Range<C>> computeNext() {
      if (!ComplementRangesByLowerBound.access$100(this.this$0).upperBound.isLessThan(this.nextComplementRangeLowerBound)
         && this.nextComplementRangeLowerBound != Cut.aboveAll()) {
         Range<C> negativeRange;
         if (this.val$positiveItr.hasNext()) {
            Range<C> positiveRange = (Range<C>)this.val$positiveItr.next();
            negativeRange = Range.create(this.nextComplementRangeLowerBound, positiveRange.lowerBound);
            this.nextComplementRangeLowerBound = positiveRange.upperBound;
         } else {
            negativeRange = Range.create(this.nextComplementRangeLowerBound, Cut.aboveAll());
            this.nextComplementRangeLowerBound = Cut.aboveAll();
         }

         return Maps.immutableEntry(negativeRange.lowerBound, negativeRange);
      } else {
         return (Entry<Cut<C>, Range<C>>)this.endOfData();
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
