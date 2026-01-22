#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class RegularContiguousSet {
public:
   const Range<C> range;
   const DiscreteDomain<C> domain;

   private RegularContiguousSet$SerializedForm(Range<C> range, DiscreteDomain<C> domain) {
      this.range = range;
      this.domain = domain;
   }

    void* readResolve() {
      return std::make_shared<RegularContiguousSet>(this.range, this.domain);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
