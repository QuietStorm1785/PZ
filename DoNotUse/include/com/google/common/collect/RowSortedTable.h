#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class RowSortedTable {
public:
    virtual ~RowSortedTable() = default;
   SortedSet<R> rowKeySet();

   SortedMap<R, Map<C, V>> rowMap();
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
