#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace google {
namespace common {
namespace math {

enum class LongMath {
    long mulMod(long a, long b, long m) {
      return a * b % m;
   }

    long squareMod(long a, long m) {
      return a * a % m;
   }
}
} // namespace math
} // namespace common
} // namespace google
} // namespace com
