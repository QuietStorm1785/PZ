#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace base {


class CharMatcher {
public:
    const CharMatcher first;
    const CharMatcher second;

   CharMatcher$Or(CharMatcher a, CharMatcher b) {
      this.first = (CharMatcher)Preconditions.checkNotNull(a);
      this.second = (CharMatcher)Preconditions.checkNotNull(b);
   }

    void setBits(BitSet table) {
      this.first.setBits(table);
      this.second.setBits(table);
   }

    bool matches(char c) {
      return this.first.matches(c) || this.second.matches(c);
   }

    std::string toString() {
      return "CharMatcher.or(" + this.first + ", " + this.second + ")";
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
