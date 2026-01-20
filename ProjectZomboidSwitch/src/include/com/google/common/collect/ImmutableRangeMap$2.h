#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace google {
namespace common {
namespace collect {

class ImmutableRangeMap {
public:
   ImmutableRangeMap$2(ImmutableRangeMap var1, ImmutableList x0, ImmutableList x1, Range var4, ImmutableRangeMap var5) {
      super(x0, x1);
      this.this$0 = var1;
      this.val$range = var4;
      this.val$outer = var5;
   }

   public ImmutableRangeMap<K, V> subRangeMap(Range<K> subRange) {
      return this.val$range.isConnected(subRange) ? this.val$outer.subRangeMap(subRange.intersection(this.val$range)) : ImmutableRangeMap.of();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
