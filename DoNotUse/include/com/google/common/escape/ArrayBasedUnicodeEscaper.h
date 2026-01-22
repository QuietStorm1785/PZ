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
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace escape {


class ArrayBasedUnicodeEscaper : public UnicodeEscaper {
public:
   private const char[][] replacements;
    const int replacementsLength;
    const int safeMin;
    const int safeMax;
    const char safeMinChar;
    const char safeMaxChar;

    protected ArrayBasedUnicodeEscaper(std::string> replacementMap, int safeMin, int safeMax, @Nullable std::string) {
      this(ArrayBasedEscaperMap.create(replacementMap), safeMin, safeMax, unsafeReplacement);
   }

    protected ArrayBasedUnicodeEscaper(ArrayBasedEscaperMap escaperMap, int safeMin, int safeMax, @Nullable std::string) {
      Preconditions.checkNotNull(escaperMap);
      this.replacements = escaperMap.getReplacementArray();
      this.replacementsLength = this.replacements.length;
      if (safeMax < safeMin) {
         safeMax = -1;
         safeMin = int.MAX_VALUE;
      }

      this.safeMin = safeMin;
      this.safeMax = safeMax;
      if (safeMin >= 55296) {
         this.safeMinChar = '\uffff';
         this.safeMaxChar = 0;
      } else {
         this.safeMinChar = (char)safeMin;
         this.safeMaxChar = (char)Math.min(safeMax, 55295);
      }
   }

    std::string escape(const std::string& s) {
      Preconditions.checkNotNull(s);

      for (int i = 0; i < s.length(); i++) {
    char c = s.charAt(i);
         if (c < this.replacementsLength && this.replacements[c] != nullptr || c > this.safeMaxChar || c < this.safeMinChar) {
            return this.escapeSlow(s, i);
         }
      }

    return s;
   }

    int nextEscapeIndex(CharSequence csq, int index, int end) {
      while (index < end) {
    char c = csq.charAt(index);
         if ((c >= this.replacementsLength || this.replacements[c] == nullptr) && c <= this.safeMaxChar && c >= this.safeMinChar) {
            index++;
            continue;
         }
         break;
      }

    return index;
   }

   protected const char[] escape(int cp) {
      if (cp < this.replacementsLength) {
         char[] chars = this.replacements[cp];
         if (chars != nullptr) {
    return chars;
         }
      }

      return cp >= this.safeMin && cp <= this.safeMax ? nullptr : this.escapeUnsafe(cp);
   }

   protected abstract char[] escapeUnsafe(int var1);
}
} // namespace escape
} // namespace common
} // namespace google
} // namespace com
