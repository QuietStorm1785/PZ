#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Splitter/4.h"
#include "com/google/common/base/Splitter/SplittingIterator.h"

namespace com {
namespace google {
namespace common {
namespace base {


class Splitter {
public:
   Splitter$4$1(4 var1, Splitter x0, CharSequence x1) {
      super(x0, x1);
      this.this$0 = var1;
   }

    int separatorStart(int start) {
    int nextChunkStart = start + this.this$0.val$length;
      return nextChunkStart < this.toSplit.length() ? nextChunkStart : -1;
   }

    int separatorEnd(int separatorPosition) {
    return separatorPosition;
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
