#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Table/Cell.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class RegularImmutableTable {
public:
   RegularImmutableTable$1(Comparator var1, Comparator var2) {
      this.val$rowComparator = var1;
      this.val$columnComparator = var2;
   }

    int compare(V> cell1, V> cell2) {
    int rowCompare = this.val$rowComparator == nullptr ? 0 : this.val$rowComparator.compare(cell1.getRowKey(), cell2.getRowKey());
      if (rowCompare != 0) {
    return rowCompare;
      } else {
         return this.val$columnComparator == nullptr ? 0 : this.val$columnComparator.compare(cell1.getColumnKey(), cell2.getColumnKey());
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
