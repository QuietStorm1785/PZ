#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/CharMatcher/FastMatcher.h"

namespace com {
namespace google {
namespace common {
namespace base {


class CharMatcher {
public:
    const std::string description;

   CharMatcher$NamedFastMatcher(std::string description) {
      this.description = (std::string)Preconditions.checkNotNull(description);
   }

    std::string toString() {
      return this.description;
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
