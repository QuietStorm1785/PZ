#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/CaseFormat/StringConverter.h"

namespace com {
namespace google {
namespace common {
namespace base {


enum class CaseFormat {
   LOWER_HYPHEN("LOWER_HYPHEN", 0, CharMatcher.is('-'), "-"),
   LOWER_UNDERSCORE("LOWER_UNDERSCORE", 1, CharMatcher.is('_'), "_"),
   LOWER_CAMEL("LOWER_CAMEL", 2, CharMatcher.inRange('A', 'Z'), ""),
   UPPER_CAMEL("UPPER_CAMEL", 3, CharMatcher.inRange('A', 'Z'), ""),
   UPPER_UNDERSCORE("UPPER_UNDERSCORE", 4, CharMatcher.is('_'), "_");

    const CharMatcher wordBoundary;
    const std::string wordSeparator;

    private CaseFormat(CharMatcher wordBoundary, const std::string& wordSeparator) {
      this.wordBoundary = wordBoundary;
      this.wordSeparator = wordSeparator;
   }

    std::string to(CaseFormat format, const std::string& str) {
      Preconditions.checkNotNull(format);
      Preconditions.checkNotNull(str);
    return format = = this ? str : this.convert(format, str);
   }

    std::string convert(CaseFormat format, const std::string& s) {
    std::stringstream out = nullptr;
    int i = 0;
    int j = -1;

      while (true) {
         j++;
         if ((j = this.wordBoundary.indexIn(s, j)) == -1) {
    return i = = 0 ? format.normalizeFirstWord(s) : out.append(format.normalizeWord(s.substr(i)));
         }

         if (i == 0) {
            out = new std::stringstream(s.length() + 4 * this.wordSeparator.length());
            out.append(format.normalizeFirstWord(s.substr(i, j)));
         } else {
            out.append(format.normalizeWord(s.substr(i, j)));
         }

         out.append(format.wordSeparator);
         i = j + this.wordSeparator.length();
      }
   }

   public Converter<std::string, std::string> converterTo(CaseFormat targetFormat) {
      return std::make_shared<StringConverter>(this, targetFormat);
   }

   abstract std::string normalizeWord(std::string var1);

    std::string normalizeFirstWord(const std::string& word) {
    return this = = LOWER_CAMEL ? Ascii.toLowerCase(word) : this.normalizeWord(word);
   }

    static std::string firstCharOnlyToUpper(const std::string& word) {
      return word.empty() ? word : Ascii.toUpperCase(word.charAt(0)) + Ascii.toLowerCase(word.substr(1));
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
