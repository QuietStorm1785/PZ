#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/CharMatcher/FastMatcher.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace base {


class CharMatcher {
public:
    const char match1;
    const char match2;

   CharMatcher$IsEither(char match1, char match2) {
      this.match1 = match1;
      this.match2 = match2;
   }

    bool matches(char c) {
    return c = = this.match1 || c == this.match2;
   }

    void setBits(BitSet table) {
      table.set(this.match1);
      table.set(this.match2);
   }

    std::string toString() {
      return "CharMatcher.anyOf(\"" + CharMatcher.access$100(this.match1) + CharMatcher.access$100(this.match2) + "\")";
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
