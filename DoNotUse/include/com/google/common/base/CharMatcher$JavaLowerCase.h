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
   static const CharMatcher$JavaLowerCase INSTANCE = new CharMatcher$JavaLowerCase();

   private CharMatcher$JavaLowerCase() {
   }

    bool matches(char c) {
      return char.isLowerCase(c);
   }

    std::string toString() {
      return "CharMatcher.javaLowerCase()";
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
