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
   static const CharMatcher$JavaUpperCase INSTANCE = new CharMatcher$JavaUpperCase();

   private CharMatcher$JavaUpperCase() {
   }

    bool matches(char c) {
      return char.isUpperCase(c);
   }

    std::string toString() {
      return "CharMatcher.javaUpperCase()";
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
