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
   static const CharMatcher$JavaIsoControl INSTANCE = new CharMatcher$JavaIsoControl();

   private CharMatcher$JavaIsoControl() {
      super("CharMatcher.javaIsoControl()");
   }

    bool matches(char c) {
      return c <= 31 || c >= 127 && c <= 159;
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
