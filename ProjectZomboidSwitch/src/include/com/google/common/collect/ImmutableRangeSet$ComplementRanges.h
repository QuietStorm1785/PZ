#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableRangeSet {
public:
    const bool positiveBoundedBelow;
    const bool positiveBoundedAbove;
    const int size;

   ImmutableRangeSet$ComplementRanges(ImmutableRangeSet var1) {
      this.this$0 = var1;
      this.positiveBoundedBelow = ((Range)ImmutableRangeSet.access$000(var1).get(0)).hasLowerBound();
      this.positiveBoundedAbove = ((Range)Iterables.getLast(ImmutableRangeSet.access$000(var1))).hasUpperBound();
    int size = ImmutableRangeSet.access$000(var1).size() - 1;
      if (this.positiveBoundedBelow) {
         size++;
      }

      if (this.positiveBoundedAbove) {
         size++;
      }

      this.size = size;
   }

    int size() {
      return this.size;
   }

   public Range<C> get(int index) {
      Preconditions.checkElementIndex(index, this.size);
      Cut<C> lowerBound;
      if (this.positiveBoundedBelow) {
         lowerBound = index == 0 ? Cut.belowAll() : ((Range)ImmutableRangeSet.access$000(this.this$0).get(index - 1)).upperBound;
      } else {
         lowerBound = ((Range)ImmutableRangeSet.access$000(this.this$0).get(index)).upperBound;
      }

      Cut<C> upperBound;
      if (this.positiveBoundedAbove && index == this.size - 1) {
         upperBound = Cut.aboveAll();
      } else {
         upperBound = ((Range)ImmutableRangeSet.access$000(this.this$0).get(index + (this.positiveBoundedBelow ? 0 : 1))).lowerBound;
      }

      return Range.create(lowerBound, upperBound);
   }

    bool isPartialView() {
    return true;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
