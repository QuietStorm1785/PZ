#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/CharMatcher/NamedFastMatcher.h"

namespace com {
namespace google {
namespace common {
namespace base {


class CharMatcher {
public:
   static const CharMatcher$Ascii INSTANCE = new CharMatcher$Ascii();

   CharMatcher$Ascii() {
      super("CharMatcher.ascii()");
   }

    bool matches(char c) {
      return c <= 127;
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
