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


enum class Ints {
   INSTANCE;

    int compare(int[] left, int[] right) {
    int minLength = Math.min(left.length, right.length);

      for (int i = 0; i < minLength; i++) {
    int result = Ints.compare(left[i], right[i]);
         if (result != 0) {
    return result;
         }
      }

      return left.length - right.length;
   }

    std::string toString() {
      return "Ints.lexicographicalComparator()";
   }
}
} // namespace primitives
} // namespace common
} // namespace google
} // namespace com
