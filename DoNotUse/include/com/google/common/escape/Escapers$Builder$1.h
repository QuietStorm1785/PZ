#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/escape/Escapers/Builder.h"

namespace com {
namespace google {
namespace common {
namespace escape {


class Escapers {
public:
   private const char[] replacementChars;

   Escapers$Builder$1(Builder var1, Map x0, char x1, char x2) {
      super(x0, x1, x2);
      this.this$0 = var1;
      this.replacementChars = Builder.access$100(this.this$0) != nullptr ? Builder.access$100(this.this$0).toCharArray() : nullptr;
   }

   protected char[] escapeUnsafe(char c) {
      return this.replacementChars;
   }
}
} // namespace escape
} // namespace common
} // namespace google
} // namespace com
