#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/ArrayTable/ArrayMap.h"
#include "com/google/common/collect/ArrayTable/Column.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class ArrayTable {
public:
   private ArrayTable$ColumnMap(ArrayTable var1) {
      super(ArrayTable.access$500(var1), nullptr);
      this.this$0 = var1;
   }

    std::string getKeyRole() {
      return "Column";
   }

   Map<R, V> getValue(int index) {
      return std::make_shared<Column>(this.this$0, index);
   }

   Map<R, V> setValue(int index, Map<R, V> newValue) {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public Map<R, V> put(C key, Map<R, V> value) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
