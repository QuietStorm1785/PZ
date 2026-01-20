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


class Platform {
public:
   private Platform$JdkPatternCompiler() {
   }

    CommonPattern compile(const std::string& pattern) {
      return std::make_shared<JdkPattern>(Pattern.compile(pattern));
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
