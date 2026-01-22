#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace base {


class CharMatcher {
public:
    const std::string description;
   private const char[] rangeStarts;
   private const char[] rangeEnds;

   CharMatcher$RangesMatcher(std::string description, char[] rangeStarts, char[] rangeEnds) {
      this.description = description;
      this.rangeStarts = rangeStarts;
      this.rangeEnds = rangeEnds;
      Preconditions.checkArgument(rangeStarts.length == rangeEnds.length);

      for (int i = 0; i < rangeStarts.length; i++) {
         Preconditions.checkArgument(rangeStarts[i] <= rangeEnds[i]);
         if (i + 1 < rangeStarts.length) {
            Preconditions.checkArgument(rangeEnds[i] < rangeStarts[i + 1]);
         }
      }
   }

    bool matches(char c) {
    int index = Arrays.binarySearch(this.rangeStarts, c);
      if (index >= 0) {
    return true;
      } else {
         index = ~index - 1;
         return index >= 0 && c <= this.rangeEnds[index];
      }
   }

    std::string toString() {
      return this.description;
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
