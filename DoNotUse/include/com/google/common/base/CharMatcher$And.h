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

   CharMatcher$And(CharMatcher a, CharMatcher b) {
      this.first = (CharMatcher)Preconditions.checkNotNull(a);
      this.second = (CharMatcher)Preconditions.checkNotNull(b);
   }

    bool matches(char c) {
      return this.first.matches(c) && this.second.matches(c);
   }

    void setBits(BitSet table) {
    BitSet tmp1 = std::make_shared<BitSet>();
      this.first.setBits(tmp1);
    BitSet tmp2 = std::make_shared<BitSet>();
      this.second.setBits(tmp2);
      tmp1.and(tmp2);
      table.or(tmp1);
   }

    std::string toString() {
      return "CharMatcher.and(" + this.first + ", " + this.second + ")";
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
