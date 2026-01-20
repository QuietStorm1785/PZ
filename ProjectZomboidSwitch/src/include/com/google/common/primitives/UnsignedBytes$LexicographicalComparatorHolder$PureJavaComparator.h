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


enum class UnsignedBytes {
   INSTANCE;

    int compare(byte[] left, byte[] right) {
    int minLength = Math.min(left.length, right.length);

      for (int i = 0; i < minLength; i++) {
    int result = UnsignedBytes.compare(left[i], right[i]);
         if (result != 0) {
    return result;
         }
      }

      return left.length - right.length;
   }

    std::string toString() {
      return "UnsignedBytes.lexicographicalComparator() (pure Java version)";
   }
}
} // namespace primitives
} // namespace common
} // namespace google
} // namespace com
