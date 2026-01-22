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

    void funnel(int from, PrimitiveSink into) {
      into.putInt(from);
   }

    std::string toString() {
      return "Funnels.integerFunnel()";
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
