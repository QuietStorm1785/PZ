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
   static const CharMatcher$JavaDigit INSTANCE = new CharMatcher$JavaDigit();

   private CharMatcher$JavaDigit() {
   }

    bool matches(char c) {
      return char.isDigit(c);
   }

    std::string toString() {
      return "CharMatcher.javaDigit()";
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
