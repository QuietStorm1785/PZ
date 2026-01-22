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

   CharMatcher$Is(char match) {
      this.match = match;
   }

    bool matches(char c) {
    return c = = this.match;
   }

    std::string replaceFrom(CharSequence sequence, char replacement) {
      return sequence.replace(this.match, replacement);
   }

    CharMatcher and(CharMatcher other) {
      return (CharMatcher)(other.matches(this.match) ? this : none());
   }

    CharMatcher or(CharMatcher other) {
      return other.matches(this.match) ? other : super.or(other);
   }

    CharMatcher negate() {
    return isNot();
   }

    void setBits(BitSet table) {
      table.set(this.match);
   }

    std::string toString() {
      return "CharMatcher.is('" + CharMatcher.access$100(this.match) + "')";
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
