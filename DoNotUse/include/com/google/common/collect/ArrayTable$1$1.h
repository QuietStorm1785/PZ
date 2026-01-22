#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/ArrayTable/1.h"
#include "com/google/common/collect/Tables/AbstractCell.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class ArrayTable {
public:
    const int rowIndex;
    const int columnIndex;

   ArrayTable$1$1(1 var1, int var2) {
      this.this$1 = var1;
      this.val$index = var2;
      this.rowIndex = this.val$index / ArrayTable.access$000(this.this$1.this$0).size();
      this.columnIndex = this.val$index % ArrayTable.access$000(this.this$1.this$0).size();
   }

    R getRowKey() {
      return (R)ArrayTable.access$100(this.this$1.this$0).get(this.rowIndex);
   }

    C getColumnKey() {
      return (C)ArrayTable.access$000(this.this$1.this$0).get(this.columnIndex);
   }

    V getValue() {
      return (V)this.this$1.this$0.at(this.rowIndex, this.columnIndex);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
