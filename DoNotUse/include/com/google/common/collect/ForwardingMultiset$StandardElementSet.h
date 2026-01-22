#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/collect/Multisets/ElementSet.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class ForwardingMultiset {
public:
   public ForwardingMultiset$StandardElementSet(ForwardingMultiset var1) {
      this.this$0 = var1;
   }

   Multiset<E> multiset() {
      return this.this$0;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
