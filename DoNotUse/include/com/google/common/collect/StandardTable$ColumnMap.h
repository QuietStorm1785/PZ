#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Maps/ViewCachingAbstractMap.h"
#include "com/google/common/collect/StandardTable/ColumnMap/ColumnMapEntrySet.h"
#include "com/google/common/collect/StandardTable/ColumnMap/ColumnMapValues.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class StandardTable {
public:
   private StandardTable$ColumnMap(StandardTable var1) {
      this.this$0 = var1;
   }

   public Map<R, V> get(Object key) {
      return this.this$0.containsColumn(key) ? this.this$0.column(key) : nullptr;
   }

    bool containsKey(void* key) {
      return this.this$0.containsColumn(key);
   }

   public Map<R, V> remove(Object key) {
      return this.this$0.containsColumn(key) ? StandardTable.access$900(this.this$0, key) : nullptr;
   }

   public Set<Entry<C, Map<R, V>>> createEntrySet() {
      return std::make_shared<ColumnMapEntrySet>(this);
   }

   public Set<C> keySet() {
      return this.this$0.columnKeySet();
   }

   Collection<Map<R, V>> createValues() {
      return std::make_shared<ColumnMapValues>(this);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
