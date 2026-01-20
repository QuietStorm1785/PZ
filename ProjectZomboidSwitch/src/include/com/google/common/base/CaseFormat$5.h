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
   CaseFormat$5(CharMatcher x0, std::string x1) {
   }

    std::string normalizeWord(const std::string& word) {
      return Ascii.toUpperCase(word);
   }

    std::string convert(CaseFormat format, const std::string& s) {
      if (format == LOWER_HYPHEN) {
         return Ascii.toLowerCase(s.replace('_', '-'));
      } else {
    return format = = LOWER_UNDERSCORE ? Ascii.toLowerCase(s) : super.convert(format, s);
      }
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
