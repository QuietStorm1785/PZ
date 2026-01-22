#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace base {


class Joiner {
public:
   Joiner$1(Joiner var1, Joiner x0, std::string var3) {
      super(x0, nullptr);
      this.this$0 = var1;
      this.val$nullText = var3;
   }

    CharSequence toString(@Nullable Object) {
      return (CharSequence)(part == nullptr ? this.val$nullText : this.this$0.toString(part));
   }

    Joiner useForNull(const std::string& nullText) {
      throw UnsupportedOperationException("already specified useForNull");
   }

    Joiner skipNulls() {
      throw UnsupportedOperationException("already specified useForNull");
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
