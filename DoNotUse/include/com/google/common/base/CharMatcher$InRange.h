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
    const char startInclusive;
    const char endInclusive;

   CharMatcher$InRange(char startInclusive, char endInclusive) {
      Preconditions.checkArgument(endInclusive >= startInclusive);
      this.startInclusive = startInclusive;
      this.endInclusive = endInclusive;
   }

    bool matches(char c) {
      return this.startInclusive <= c && c <= this.endInclusive;
   }

    void setBits(BitSet table) {
      table.set(this.startInclusive, this.endInclusive + 1);
   }

    std::string toString() {
      return "CharMatcher.inRange('" + CharMatcher.access$100(this.startInclusive) + "', '" + CharMatcher.access$100(this.endInclusive) + "')";
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
