#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/annotations/VisibleForTesting.h"
#include "com/google/common/base/CharMatcher/NamedFastMatcher.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace base {


class CharMatcher {
public:
    static const std::string TABLE = " 　\r\u0085   　\u2029\u000b　   　 \t     \f 　 　　\u2028\n 　";
    static const int MULTIPLIER = 1682554634;
    static const int SHIFT = int.numberOfLeadingZeros(" 　\r\u0085   　\u2029\u000b　   　 \t     \f 　 　　\u2028\n 　".length() - 1);
   static const CharMatcher$Whitespace INSTANCE = new CharMatcher$Whitespace();

   CharMatcher$Whitespace() {
      super("CharMatcher.whitespace()");
   }

    bool matches(char c) {
      return " 　\r\u0085   　\u2029\u000b　   　 \t     \f 　 　　\u2028\n 　".charAt(1682554634 * c >>> SHIFT) == c;
   }

    void setBits(BitSet table) {
      for (int i = 0; i < " 　\r\u0085   　\u2029\u000b　   　 \t     \f 　 　　\u2028\n 　".length(); i++) {
         table.set(" 　\r\u0085   　\u2029\u000b　   　 \t     \f 　 　　\u2028\n 　".charAt(i));
      }
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
