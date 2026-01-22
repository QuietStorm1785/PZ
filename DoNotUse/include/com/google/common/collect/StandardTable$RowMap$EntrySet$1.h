#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Function.h"
#include "com/google/common/collect/StandardTable/RowMap/EntrySet.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class StandardTable {
public:
   StandardTable$RowMap$EntrySet$1(EntrySet var1) {
      this.this$2 = var1;
   }

   public Map<C, V> apply(R rowKey) {
      return this.this$2.this$1.this$0.row(rowKey);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
