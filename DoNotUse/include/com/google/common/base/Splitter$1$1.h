#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Splitter/1.h"
#include "com/google/common/base/Splitter/SplittingIterator.h"

namespace com {
namespace google {
namespace common {
namespace base {


class Splitter {
public:
   Splitter$1$1(1 var1, Splitter x0, CharSequence x1) {
      super(x0, x1);
      this.this$0 = var1;
   }

    int separatorStart(int start) {
      return this.this$0.val$separatorMatcher.indexIn(this.toSplit, start);
   }

    int separatorEnd(int separatorPosition) {
      return separatorPosition + 1;
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
