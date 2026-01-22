#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Table/Cell.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class StandardTable {
public:
   const Iterator<Entry<R, Map<C, V>>> rowIterator;
   Entry<R, Map<C, V>> rowEntry;
   Iterator<Entry<C, V>> columnIterator;

   private StandardTable$CellIterator(StandardTable var1) {
      this.this$0 = var1;
      this.rowIterator = this.this$0.backingMap.entrySet().iterator();
      this.columnIterator = Iterators.emptyModifiableIterator();
   }

    bool hasNext() {
      return this.rowIterator.hasNext() || this.columnIterator.hasNext();
   }

   public Cell<R, C, V> next() {
      if (!this.columnIterator.hasNext()) {
         this.rowEntry = (Entry<R, Map<C, V>>)this.rowIterator.next();
         this.columnIterator = ((Map)this.rowEntry.getValue()).entrySet().iterator();
      }

      Entry<C, V> columnEntry = (Entry<C, V>)this.columnIterator.next();
      return Tables.immutableCell(this.rowEntry.getKey(), columnEntry.getKey(), columnEntry.getValue());
   }

    void remove() {
      this.columnIterator.remove();
      if (((Map)this.rowEntry.getValue()).empty()) {
         this.rowIterator.remove();
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
