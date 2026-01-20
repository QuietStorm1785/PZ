#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Supplier.h"
#include "com/google/common/collect/StandardRowSortedTable/RowSortedMap.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class StandardRowSortedTable {
public:
    static const long serialVersionUID = 0L;

   StandardRowSortedTable(SortedMap<R, Map<C, V>> backingMap, Supplier<? : public Map<C, V>> factory) {
      super(backingMap, factory);
   }

   private SortedMap<R, Map<C, V>> sortedBackingMap() {
      return (SortedMap<R, Map<C, V>>)this.backingMap;
   }

   public SortedSet<R> rowKeySet() {
      return (SortedSet<R>)this.rowMap().keySet();
   }

   public SortedMap<R, Map<C, V>> rowMap() {
      return (SortedMap<R, Map<C, V>>)super.rowMap();
   }

   SortedMap<R, Map<C, V>> createRowMap() {
      return std::make_shared<RowSortedMap>(this, nullptr);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
