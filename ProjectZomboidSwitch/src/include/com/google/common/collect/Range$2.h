#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Function.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class Range {
public:
    Cut apply(Range range) {
      return range.upperBound;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
