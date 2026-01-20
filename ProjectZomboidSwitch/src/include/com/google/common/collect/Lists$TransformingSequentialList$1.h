#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Lists/TransformingSequentialList.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Lists {
public:
   Lists$TransformingSequentialList$1(TransformingSequentialList var1, ListIterator x0) {
      super(x0);
      this.this$0 = var1;
   }

    T transform(F from) {
      return (T)this.this$0.function.apply(from);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
