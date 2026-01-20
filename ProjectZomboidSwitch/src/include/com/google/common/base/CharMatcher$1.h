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
   CharMatcher$1(CharMatcher var1, CharMatcher x0, std::string var3) {
      super(x0);
      this.this$0 = var1;
      this.val$description = var3;
   }

    std::string toString() {
      return this.val$description;
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
