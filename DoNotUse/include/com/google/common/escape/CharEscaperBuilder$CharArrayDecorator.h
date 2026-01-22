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
namespace escape {

class CharEscaperBuilder {
public:
   private const char[][] replacements;
    const int replaceLength;

   CharEscaperBuilder$CharArrayDecorator(char[][] replacements) {
      this.replacements = replacements;
      this.replaceLength = replacements.length;
   }

    std::string escape(const std::string& s) {
    int slen = s.length();

      for (int index = 0; index < slen; index++) {
    char c = s.charAt(index);
         if (c < this.replacements.length && this.replacements[c] != nullptr) {
            return this.escapeSlow(s, index);
         }
      }

    return s;
   }

   protected char[] escape(char c) {
      return c < this.replaceLength ? this.replacements[c] : nullptr;
   }
}
} // namespace escape
} // namespace common
} // namespace google
} // namespace com
