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
   static const CharMatcher$JavaLetter INSTANCE = new CharMatcher$JavaLetter();

   private CharMatcher$JavaLetter() {
   }

    bool matches(char c) {
      return char.isLetter(c);
   }

    std::string toString() {
      return "CharMatcher.javaLetter()";
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
