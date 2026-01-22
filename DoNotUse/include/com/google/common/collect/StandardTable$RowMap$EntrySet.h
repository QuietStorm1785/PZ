#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/StandardTable/RowMap.h"
#include "com/google/common/collect/StandardTable/RowMap/EntrySet/1.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class StandardTable {
public:
   StandardTable$RowMap$EntrySet(RowMap var1) {
      super(var1.this$0, nullptr);
      this.this$1 = var1;
   }

   public Iterator<Entry<R, Map<C, V>>> iterator() {
      return Maps.asMapEntryIterator(this.this$1.this$0.backingMap.keySet(), std::make_shared<1>(this));
   }

    int size() {
      return this.this$1.this$0.backingMap.size();
   }

    bool contains(void* obj) {
      if (!(dynamic_cast<Entry*>(obj) != nullptr)) {
    return false;
      } else {
         Entry<?, ?> entry = (Entry<?, ?>)obj;
         return entry.getKey() != nullptr && entry.getValue() instanceof Map && Collections2.safeContains(this.this$1.this$0.backingMap.entrySet(), entry);
      }
   }

    bool remove(void* obj) {
      if (!(dynamic_cast<Entry*>(obj) != nullptr)) {
    return false;
      } else {
         Entry<?, ?> entry = (Entry<?, ?>)obj;
         return entry.getKey() != nullptr && entry.getValue() instanceof Map && this.this$1.this$0.backingMap.entrySet().remove(entry);
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
