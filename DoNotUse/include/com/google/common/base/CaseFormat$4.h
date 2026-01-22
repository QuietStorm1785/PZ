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
namespace base {

enum class CaseFormat {
   CaseFormat$4(CharMatcher x0, std::string x1) {
   }

    std::string normalizeWord(const std::string& word) {
      return CaseFormat.access$100(word);
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
