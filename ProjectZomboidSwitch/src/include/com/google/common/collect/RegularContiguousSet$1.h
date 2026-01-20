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

class RegularContiguousSet {
public:
    const C last;

   RegularContiguousSet$1(RegularContiguousSet var1, Comparable x0) {
      super(x0);
      this.this$0 = var1;
      this.last = (C)this.this$0.last();
   }

    C computeNext(C previous) {
      return (C)(RegularContiguousSet.access$000(previous, this.last) ? nullptr : this.this$0.domain.next(previous));
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
