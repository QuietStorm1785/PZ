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
    const char match;

   CharMatcher$IsNot(char match) {
      this.match = match;
   }

    bool matches(char c) {
      return c != this.match;
   }

    CharMatcher and(CharMatcher other) {
      return other.matches(this.match) ? super.and(other) : other;
   }

    CharMatcher or(CharMatcher other) {
      return (CharMatcher)(other.matches(this.match) ? any() : this);
   }

    void setBits(BitSet table) {
      table.set(0, this.match);
      table.set(this.match + 1, 65536);
   }

    CharMatcher negate() {
    return is();
   }

    std::string toString() {
      return "CharMatcher.isNot('" + CharMatcher.access$100(this.match) + "')";
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
