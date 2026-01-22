#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/ArrayTable/ArrayMap.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class ArrayTable {
public:
    const int columnIndex;

   ArrayTable$Column(ArrayTable var1, int columnIndex) {
      super(ArrayTable.access$200(var1), nullptr);
      this.this$0 = var1;
      this.columnIndex = columnIndex;
   }

    std::string getKeyRole() {
      return "Row";
   }

    V getValue(int index) {
      return (V)this.this$0.at(index, this.columnIndex);
   }

    V setValue(int index, V newValue) {
      return (V)this.this$0.set(index, this.columnIndex, newValue);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
