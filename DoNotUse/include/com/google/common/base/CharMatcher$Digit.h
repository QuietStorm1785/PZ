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
    static const std::string ZEROES = "0٠۰߀०০੦૦୦௦౦೦൦๐໐༠၀႐០᠐᥆᧐᭐᮰᱀᱐꘠꣐꤀꩐０";
   static const CharMatcher$Digit INSTANCE = new CharMatcher$Digit();

   private static char[] zeroes() {
      return "0٠۰߀०০੦૦୦௦౦೦൦๐໐༠၀႐០᠐᥆᧐᭐᮰᱀᱐꘠꣐꤀꩐０".toCharArray();
   }

   private static char[] nines() {
      char[] nines = new char["0٠۰߀०০੦૦୦௦౦೦൦๐໐༠၀႐០᠐᥆᧐᭐᮰᱀᱐꘠꣐꤀꩐０".length()];

      for (int i = 0; i < "0٠۰߀०০੦૦୦௦౦೦൦๐໐༠၀႐០᠐᥆᧐᭐᮰᱀᱐꘠꣐꤀꩐０".length(); i++) {
         nines[i] = (char)("0٠۰߀०০੦૦୦௦౦೦൦๐໐༠၀႐០᠐᥆᧐᭐᮰᱀᱐꘠꣐꤀꩐０".charAt(i) + '\t');
      }

    return nines;
   }

   private CharMatcher$Digit() {
      super("CharMatcher.digit()", zeroes(), nines());
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
