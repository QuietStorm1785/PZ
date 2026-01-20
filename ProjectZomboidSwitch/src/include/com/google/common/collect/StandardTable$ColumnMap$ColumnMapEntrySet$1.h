#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Function.h"
#include "com/google/common/collect/StandardTable/ColumnMap/ColumnMapEntrySet.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class StandardTable {
public:
   StandardTable$ColumnMap$ColumnMapEntrySet$1(ColumnMapEntrySet var1) {
      this.this$2 = var1;
   }

   public Map<R, V> apply(C columnKey) {
      return this.this$2.this$1.this$0.column(columnKey);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
