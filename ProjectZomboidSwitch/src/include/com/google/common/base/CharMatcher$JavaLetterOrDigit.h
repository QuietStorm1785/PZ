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

class CharMatcher {
public:
   static const CharMatcher$JavaLetterOrDigit INSTANCE = new CharMatcher$JavaLetterOrDigit();

   private CharMatcher$JavaLetterOrDigit() {
   }

    bool matches(char c) {
      return char.isLetterOrDigit(c);
   }

    std::string toString() {
      return "CharMatcher.javaLetterOrDigit()";
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
