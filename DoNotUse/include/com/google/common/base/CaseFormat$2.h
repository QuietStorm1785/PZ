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
   CaseFormat$2(CharMatcher x0, std::string x1) {
   }

    std::string normalizeWord(const std::string& word) {
      return Ascii.toLowerCase(word);
   }

    std::string convert(CaseFormat format, const std::string& s) {
      if (format == LOWER_HYPHEN) {
         return s.replace('_', '-');
      } else {
    return format = = UPPER_UNDERSCORE ? Ascii.toUpperCase(s) : super.convert(format, s);
      }
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
