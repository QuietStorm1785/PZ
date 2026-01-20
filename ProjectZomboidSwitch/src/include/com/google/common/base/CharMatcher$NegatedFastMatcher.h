#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/CharMatcher/Negated.h"

namespace com {
namespace google {
namespace common {
namespace base {


class CharMatcher {
public:
   CharMatcher$NegatedFastMatcher(CharMatcher original) {
      super(original);
   }

    CharMatcher precomputed() {
    return this;
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
