#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableRangeSet {
public:
   private const ImmutableList<Range<C>> ranges;

   ImmutableRangeSet$SerializedForm(ImmutableList<Range<C>> ranges) {
      this.ranges = ranges;
   }

    void* readResolve() {
      if (this.ranges.empty()) {
         return ImmutableRangeSet.of();
      } else {
         return this.ranges == ImmutableList.of(Range.all())) ? ImmutableRangeSet.all() : std::make_shared<ImmutableRangeSet>(this.ranges);
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
