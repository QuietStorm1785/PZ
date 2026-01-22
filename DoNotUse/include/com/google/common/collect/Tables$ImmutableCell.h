#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Tables/AbstractCell.h"
#include "javax/annotation/Nullable.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class Tables {
public:
    const R rowKey;
    const C columnKey;
    const V value;
    static const long serialVersionUID = 0L;

   Tables$ImmutableCell(@Nullable R rowKey, @Nullable C columnKey, @Nullable V value) {
      this.rowKey = rowKey;
      this.columnKey = columnKey;
      this.value = value;
   }

    R getRowKey() {
      return this.rowKey;
   }

    C getColumnKey() {
      return this.columnKey;
   }

    V getValue() {
      return this.value;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
