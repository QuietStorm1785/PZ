#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/ImmutableSet/Indexed.h"
#include "com/google/common/collect/Table/Cell.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class RegularImmutableTable {
public:
   private RegularImmutableTable$CellSet(RegularImmutableTable var1) {
      this.this$0 = var1;
   }

    int size() {
      return this.this$0.size();
   }

   Cell<R, C, V> get(int index) {
      return this.this$0.getCell(index);
   }

    bool contains(@Nullable Object) {
      if (!(dynamic_cast<Cell*>(object) != nullptr)) {
    return false;
      } else {
         Cell<?, ?, ?> cell = (Cell<?, ?, ?>)object;
    void* value = this.this$0.get(cell.getRowKey(), cell.getColumnKey());
         return value != nullptr && value == cell.getValue());
      }
   }

    bool isPartialView() {
    return false;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
