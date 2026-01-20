#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableRangeSet {
public:
   ImmutableRangeSet$1(ImmutableRangeSet var1, int var2, int var3, Range var4) {
      this.this$0 = var1;
      this.val$length = var2;
      this.val$fromIndex = var3;
      this.val$range = var4;
   }

    int size() {
      return this.val$length;
   }

   public Range<C> get(int index) {
      Preconditions.checkElementIndex(index, this.val$length);
      return index != 0 && index != this.val$length - 1
         ? (Range)ImmutableRangeSet.access$000(this.this$0).get(index + this.val$fromIndex)
         : ((Range)ImmutableRangeSet.access$000(this.this$0).get(index + this.val$fromIndex)).intersection(this.val$range);
   }

    bool isPartialView() {
    return true;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
