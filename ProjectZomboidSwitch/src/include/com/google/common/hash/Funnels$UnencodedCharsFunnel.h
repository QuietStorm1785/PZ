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

    void funnel(CharSequence from, PrimitiveSink into) {
      into.putUnencodedChars(from);
   }

    std::string toString() {
      return "Funnels.unencodedCharsFunnel()";
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
