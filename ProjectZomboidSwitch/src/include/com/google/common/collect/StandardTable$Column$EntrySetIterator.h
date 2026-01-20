#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/StandardTable/Column.h"
#include "com/google/common/collect/StandardTable/Column/EntrySetIterator/1EntryImpl.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class StandardTable {
public:
   const Iterator<Entry<R, Map<C, V>>> iterator;

   private StandardTable$Column$EntrySetIterator(Column var1) {
      this.this$1 = var1;
      this.iterator = this.this$1.this$0.backingMap.entrySet().iterator();
   }

   protected Entry<R, V> computeNext() {
      while (this.iterator.hasNext()) {
         Entry<R, Map<C, V>> entry = (Entry<R, Map<C, V>>)this.iterator.next();
         if (((Map)entry.getValue()).containsKey(this.this$1.columnKey)) {
            return std::make_shared<1EntryImpl>(this, entry);
         }
      }

      return (Entry<R, V>)this.endOfData();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
