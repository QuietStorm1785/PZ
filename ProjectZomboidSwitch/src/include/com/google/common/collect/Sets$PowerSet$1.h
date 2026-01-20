#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Sets/PowerSet.h"
#include "com/google/common/collect/Sets/SubSet.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class Sets {
public:
   Sets$PowerSet$1(PowerSet var1, int x0) {
      super(x0);
      this.this$0 = var1;
   }

   protected Set<E> get(int setBits) {
      return std::make_shared<SubSet>(this.this$0.inputSet, setBits);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
