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


class Range {
public:
    static const long serialVersionUID = 0L;

   private Range$RangeLexOrdering() {
   }

    int compare(Range<?> left, Range<?> right) {
      return ComparisonChain.start().compare(left.lowerBound, right.lowerBound).compare(left.upperBound, right.upperBound).result();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
