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
   private const DiscreteDomain<C> domain;

   ImmutableRangeSet$AsSetSerializedForm(ImmutableList<Range<C>> ranges, DiscreteDomain<C> domain) {
      this.ranges = ranges;
      this.domain = domain;
   }

    void* readResolve() {
      return std::make_shared<ImmutableRangeSet>(this.ranges).asSet(this.domain);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
