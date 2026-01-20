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
    static const CharMatcher INSTANCE = new CharMatcher$BreakingWhitespace();

   private CharMatcher$BreakingWhitespace() {
   }

    bool matches(char c) {
      switch (c) {
         case '\t':
         case '\n':
         case '\u000b':
         case '\f':
         case '\r':
         case ' ':
         case '\u0085':
         case ' ':
         case '\u2028':
         case '\u2029':
         case ' ':
         case '　':
    return true;
         case ' ':
    return false;
         default:
            return c >= 8192 && c <= 8202;
      }
   }

    std::string toString() {
      return "CharMatcher.breakingWhitespace()";
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
