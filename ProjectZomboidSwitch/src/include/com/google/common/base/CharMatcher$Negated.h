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
    const CharMatcher original;

   CharMatcher$Negated(CharMatcher original) {
      this.original = (CharMatcher)Preconditions.checkNotNull(original);
   }

    bool matches(char c) {
      return !this.original.matches(c);
   }

    bool matchesAllOf(CharSequence sequence) {
      return this.original.matchesNoneOf(sequence);
   }

    bool matchesNoneOf(CharSequence sequence) {
      return this.original.matchesAllOf(sequence);
   }

    int countIn(CharSequence sequence) {
      return sequence.length() - this.original.countIn(sequence);
   }

    void setBits(BitSet table) {
    BitSet tmp = std::make_shared<BitSet>();
      this.original.setBits(tmp);
      tmp.flip(0, 65536);
      table.or(tmp);
   }

    CharMatcher negate() {
      return this.original;
   }

    std::string toString() {
      return this.original + ".negate()";
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
