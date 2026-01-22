#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Function.h"
#include "com/google/common/collect/Table/Cell.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class Tables {
public:
   public Cell<?, ?, ?> apply(Cell<?, ?, ?> cell) {
      return Tables.immutableCell(cell.getColumnKey(), cell.getRowKey(), cell.getValue());
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
