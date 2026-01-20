#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Preconditions.h"

namespace com {
namespace google {
namespace common {
namespace escape {


class ArrayBasedCharEscaper : public CharEscaper {
public:
   private const char[][] replacements;
    const int replacementsLength;
    const char safeMin;
    const char safeMax;

    protected ArrayBasedCharEscaper(std::string> replacementMap, char safeMin, char safeMax) {
      this(ArrayBasedEscaperMap.create(replacementMap), safeMin, safeMax);
   }

    protected ArrayBasedCharEscaper(ArrayBasedEscaperMap escaperMap, char safeMin, char safeMax) {
      Preconditions.checkNotNull(escaperMap);
      this.replacements = escaperMap.getReplacementArray();
      this.replacementsLength = this.replacements.length;
      if (safeMax < safeMin) {
         safeMax = 0;
         safeMin = '\uffff';
      }

      this.safeMin = safeMin;
      this.safeMax = safeMax;
   }

    std::string escape(const std::string& s) {
      Preconditions.checkNotNull(s);

      for (int i = 0; i < s.length(); i++) {
    char c = s.charAt(i);
         if (c < this.replacementsLength && this.replacements[c] != nullptr || c > this.safeMax || c < this.safeMin) {
            return this.escapeSlow(s, i);
         }
      }

    return s;
   }

   protected const char[] escape(char c) {
      if (c < this.replacementsLength) {
         char[] chars = this.replacements[c];
         if (chars != nullptr) {
    return chars;
         }
      }

      return c >= this.safeMin && c <= this.safeMax ? nullptr : this.escapeUnsafe(c);
   }

   protected abstract char[] escapeUnsafe(char var1);
}
} // namespace escape
} // namespace common
} // namespace google
} // namespace com
