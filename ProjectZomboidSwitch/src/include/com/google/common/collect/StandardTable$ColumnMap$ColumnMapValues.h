#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/Maps/Values.h"
#include "com/google/common/collect/StandardTable/ColumnMap.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class StandardTable {
public:
   StandardTable$ColumnMap$ColumnMapValues(ColumnMap var1) {
      super(var1);
      this.this$1 = var1;
   }

    bool remove(void* obj) {
      for (Entry<C, Map<R, V>> entry : this.this$1.entrySet()) {
         if (((Map)entry.getValue()) == obj)) {
            StandardTable.access$900(this.this$1.this$0, entry.getKey());
    return true;
         }
      }

    return false;
   }

    bool removeAll(Collection<?> c) {
      Preconditions.checkNotNull(c);
    bool changed = false;

      for (C columnKey : Lists.newArrayList(this.this$1.this$0.columnKeySet().iterator())) {
         if (c.contains(this.this$1.this$0.column(columnKey))) {
            StandardTable.access$900(this.this$1.this$0, columnKey);
            changed = true;
         }
      }

    return changed;
   }

    bool retainAll(Collection<?> c) {
      Preconditions.checkNotNull(c);
    bool changed = false;

      for (C columnKey : Lists.newArrayList(this.this$1.this$0.columnKeySet().iterator())) {
         if (!c.contains(this.this$1.this$0.column(columnKey))) {
            StandardTable.access$900(this.this$1.this$0, columnKey);
            changed = true;
         }
      }

    return changed;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
