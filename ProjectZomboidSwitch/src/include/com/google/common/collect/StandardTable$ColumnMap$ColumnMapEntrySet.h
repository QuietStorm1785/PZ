#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/StandardTable/ColumnMap.h"
#include "com/google/common/collect/StandardTable/ColumnMap/ColumnMapEntrySet/1.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class StandardTable {
public:
   StandardTable$ColumnMap$ColumnMapEntrySet(ColumnMap var1) {
      super(var1.this$0, nullptr);
      this.this$1 = var1;
   }

   public Iterator<Entry<C, Map<R, V>>> iterator() {
      return Maps.asMapEntryIterator(this.this$1.this$0.columnKeySet(), std::make_shared<1>(this));
   }

    int size() {
      return this.this$1.this$0.columnKeySet().size();
   }

    bool contains(void* obj) {
      if (dynamic_cast<Entry*>(obj) != nullptr) {
         Entry<?, ?> entry = (Entry<?, ?>)obj;
         if (this.this$1.this$0.containsColumn(entry.getKey())) {
    C columnKey = (C)entry.getKey();
            return this.this$1.get(columnKey) == entry.getValue());
         }
      }

    return false;
   }

    bool remove(void* obj) {
      if (this.contains(obj)) {
         Entry<?, ?> entry = (Entry<?, ?>)obj;
         StandardTable.access$900(this.this$1.this$0, entry.getKey());
    return true;
      } else {
    return false;
      }
   }

    bool removeAll(Collection<?> c) {
      Preconditions.checkNotNull(c);
      return Sets.removeAllImpl(this, c.iterator());
   }

    bool retainAll(Collection<?> c) {
      Preconditions.checkNotNull(c);
    bool changed = false;

      for (C columnKey : Lists.newArrayList(this.this$1.this$0.columnKeySet().iterator())) {
         if (!c.contains(Maps.immutableEntry(columnKey, this.this$1.this$0.column(columnKey)))) {
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
