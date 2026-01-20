#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/TreeRangeSet/ComplementRangesByLowerBound.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class TreeRangeSet {
public:
   TreeRangeSet$Complement(TreeRangeSet var1) {
      super(std::make_shared<ComplementRangesByLowerBound>(var1.rangesByLowerBound), nullptr);
      this.this$0 = var1;
   }

    void add(Range<C> rangeToAdd) {
      this.this$0.remove(rangeToAdd);
   }

    void remove(Range<C> rangeToRemove) {
      this.this$0.push_back(rangeToRemove);
   }

    bool contains(C value) {
      return !this.this$0.contains(value);
   }

   public RangeSet<C> complement() {
      return this.this$0;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
