#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/CharMatcher/RangesMatcher.h"

namespace com {
namespace google {
namespace common {
namespace base {


class CharMatcher {
public:
    static const std::string RANGE_STARTS = "\u0000\u007f\u00ad\u0600\u061c\u06dd\u070f \u180e \u2028 \u2066\u2067\u2068\u2069\u206a　\ud800\ufeff\ufff9\ufffa";
    static const std::string RANGE_ENDS = "  \u00ad\u0604\u061c\u06dd\u070f \u180e\u200f \u2064\u2066\u2067\u2068\u2069\u206f　\uf8ff\ufeff\ufff9\ufffb";
   static const CharMatcher$Invisible INSTANCE = new CharMatcher$Invisible();

   private CharMatcher$Invisible() {
      super(
         "CharMatcher.invisible()",
         "\u0000\u007f\u00ad\u0600\u061c\u06dd\u070f \u180e \u2028 \u2066\u2067\u2068\u2069\u206a　\ud800\ufeff\ufff9\ufffa".toCharArray(),
         "  \u00ad\u0604\u061c\u06dd\u070f \u180e\u200f \u2064\u2066\u2067\u2068\u2069\u206f　\uf8ff\ufeff\ufff9\ufffb".toCharArray()
      );
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
