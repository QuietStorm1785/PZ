#pragma once
#include <sstream>
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
   private const char[] chars;

   public CharMatcher$AnyOf(CharSequence chars) {
      this.chars = chars.toCharArray();
      Arrays.sort(this.chars);
   }

    bool matches(char c) {
      return Arrays.binarySearch(this.chars, c) >= 0;
   }

    void setBits(BitSet table) {
      for (char c : this.chars) {
         table.set(c);
      }
   }

    std::string toString() {
    std::stringstream description = new std::stringstream("CharMatcher.anyOf(\"");

      for (char c : this.chars) {
         description.append(CharMatcher.access$100(c));
      }

      description.append("\")");
      return description;
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
