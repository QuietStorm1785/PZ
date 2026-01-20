#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Function.h"
#include "com/google/common/collect/Tables/TransformedTable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class Tables {
public:
   Tables$TransformedTable$2(TransformedTable var1) {
      this.this$0 = var1;
   }

   public Map<C, V2> apply(Map<C, V1> row) {
      return Maps.transformValues(row, this.this$0.function);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
