#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/CharMatcher/NegatedFastMatcher.h"

namespace com {
namespace google {
namespace common {
namespace base {


class CharMatcher {
public:
    CharMatcher precomputed() {
    return this;
   }

    CharMatcher negate() {
      return std::make_shared<NegatedFastMatcher>(this);
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
