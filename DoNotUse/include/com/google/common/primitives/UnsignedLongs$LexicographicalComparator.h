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
namespace primitives {


enum class UnsignedLongs {
   INSTANCE;

    int compare(long[] left, long[] right) {
    int minLength = Math.min(left.length, right.length);

      for (int i = 0; i < minLength; i++) {
         if (left[i] != right[i]) {
            return UnsignedLongs.compare(left[i], right[i]);
         }
      }

      return left.length - right.length;
   }

    std::string toString() {
      return "UnsignedLongs.lexicographicalComparator()";
   }
}
} // namespace primitives
} // namespace common
} // namespace google
} // namespace com
