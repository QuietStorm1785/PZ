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
namespace hash {

enum class Funnels {
   INSTANCE;

    void funnel(long from, PrimitiveSink into) {
      into.putLong(from);
   }

    std::string toString() {
      return "Funnels.longFunnel()";
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
