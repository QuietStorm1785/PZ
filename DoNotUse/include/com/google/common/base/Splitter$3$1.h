#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Splitter/3.h"
#include "com/google/common/base/Splitter/SplittingIterator.h"

namespace com {
namespace google {
namespace common {
namespace base {


class Splitter {
public:
   Splitter$3$1(3 var1, Splitter x0, CharSequence x1, CommonMatcher var4) {
      super(x0, x1);
      this.this$0 = var1;
      this.val$matcher = var4;
   }

    int separatorStart(int start) {
      return this.val$matcher.find(start) ? this.val$matcher.start() : -1;
   }

    int separatorEnd(int separatorPosition) {
      return this.val$matcher.end();
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
