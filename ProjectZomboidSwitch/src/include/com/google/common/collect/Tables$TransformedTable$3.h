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
   Tables$TransformedTable$3(TransformedTable var1) {
      this.this$0 = var1;
   }

   public Map<R, V2> apply(Map<R, V1> column) {
      return Maps.transformValues(column, this.this$0.function);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
