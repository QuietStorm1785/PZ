#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Maps/ViewCachingAbstractMap.h"
#include "com/google/common/collect/StandardTable/RowMap/EntrySet.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class StandardTable {
public:
   StandardTable$RowMap(StandardTable var1) {
      this.this$0 = var1;
   }

    bool containsKey(void* key) {
      return this.this$0.containsRow(key);
   }

   public Map<C, V> get(Object key) {
      return this.this$0.containsRow(key) ? this.this$0.row(key) : nullptr;
   }

   public Map<C, V> remove(Object key) {
    return key = = nullptr ? nullptr : (Map)this.this$0.backingMap.remove(key);
   }

   protected Set<Entry<R, Map<C, V>>> createEntrySet() {
      return std::make_shared<EntrySet>(this);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
