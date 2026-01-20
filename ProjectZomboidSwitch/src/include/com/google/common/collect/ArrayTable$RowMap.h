#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/ArrayTable/ArrayMap.h"
#include "com/google/common/collect/ArrayTable/Row.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class ArrayTable {
public:
   private ArrayTable$RowMap(ArrayTable var1) {
      super(ArrayTable.access$200(var1), nullptr);
      this.this$0 = var1;
   }

    std::string getKeyRole() {
      return "Row";
   }

   Map<C, V> getValue(int index) {
      return std::make_shared<Row>(this.this$0, index);
   }

   Map<C, V> setValue(int index, Map<C, V> newValue) {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public Map<C, V> put(R key, Map<C, V> value) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
