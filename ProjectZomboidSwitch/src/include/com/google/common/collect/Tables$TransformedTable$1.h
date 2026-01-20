#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Function.h"
#include "com/google/common/collect/Table/Cell.h"
#include "com/google/common/collect/Tables/TransformedTable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class Tables {
public:
   Tables$TransformedTable$1(TransformedTable var1) {
      this.this$0 = var1;
   }

   public Cell<R, C, V2> apply(Cell<R, C, V1> cell) {
      return Tables.immutableCell(cell.getRowKey(), cell.getColumnKey(), this.this$0.function.apply(cell.getValue()));
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
