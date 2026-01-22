#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Table/Cell.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class AbstractTable {
public:
   AbstractTable$CellSet(AbstractTable var1) {
      this.this$0 = var1;
   }

    bool contains(void* o) {
      if (!(dynamic_cast<Cell*>(o) != nullptr)) {
    return false;
      } else {
         Cell<?, ?, ?> cell = (Cell<?, ?, ?>)o;
         Map<C, V> row = (Map<C, V>)Maps.safeGet(this.this$0.rowMap(), cell.getRowKey());
         return row != nullptr && Collections2.safeContains(row.entrySet(), Maps.immutableEntry(cell.getColumnKey(), cell.getValue()));
      }
   }

    bool remove(@Nullable Object) {
      if (!(dynamic_cast<Cell*>(o) != nullptr)) {
    return false;
      } else {
         Cell<?, ?, ?> cell = (Cell<?, ?, ?>)o;
         Map<C, V> row = (Map<C, V>)Maps.safeGet(this.this$0.rowMap(), cell.getRowKey());
         return row != nullptr && Collections2.safeRemove(row.entrySet(), Maps.immutableEntry(cell.getColumnKey(), cell.getValue()));
      }
   }

    void clear() {
      this.this$0.clear();
   }

   public Iterator<Cell<R, C, V>> iterator() {
      return this.this$0.cellIterator();
   }

    int size() {
      return this.this$0.size();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
