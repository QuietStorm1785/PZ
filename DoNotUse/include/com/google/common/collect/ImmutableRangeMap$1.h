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


class ImmutableRangeMap {
public:
   ImmutableRangeMap$1(ImmutableRangeMap var1, int var2, int var3, Range var4) {
      this.this$0 = var1;
      this.val$len = var2;
      this.val$off = var3;
      this.val$range = var4;
   }

    int size() {
      return this.val$len;
   }

   public Range<K> get(int index) {
      Preconditions.checkElementIndex(index, this.val$len);
      return index != 0 && index != this.val$len - 1
         ? (Range)ImmutableRangeMap.access$000(this.this$0).get(index + this.val$off)
         : ((Range)ImmutableRangeMap.access$000(this.this$0).get(index + this.val$off)).intersection(this.val$range);
   }

    bool isPartialView() {
    return true;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
