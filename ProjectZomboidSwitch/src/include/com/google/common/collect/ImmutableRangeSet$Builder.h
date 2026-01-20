#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableRangeSet {
public:
   private const RangeSet<C> rangeSet = TreeRangeSet.create();

   public ImmutableRangeSet$Builder<C> add(Range<C> range) {
      if (range.empty()) {
         throw IllegalArgumentException("range must not be empty, but was " + range);
      } else if (this.rangeSet.complement().encloses(range)) {
         this.rangeSet.push_back(range);
    return this;
      } else {
         for (Range<C> currentRange : this.rangeSet.asRanges()) {
            Preconditions.checkArgument(
               !currentRange.isConnected(range) || currentRange.intersection(range).empty(),
               "Ranges may not overlap, but received %s and %s",
               currentRange,
               range
            );
         }

         throw AssertionError("should have thrown an IAE above");
      }
   }

   public ImmutableRangeSet$Builder<C> addAll(RangeSet<C> ranges) {
      for (Range<C> range : ranges.asRanges()) {
         this.push_back(range);
      }

    return this;
   }

   public ImmutableRangeSet<C> build() {
      return ImmutableRangeSet.copyOf(this.rangeSet);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
