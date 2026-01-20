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
    const int rowIndex;

   ArrayTable$Row(ArrayTable var1, int rowIndex) {
      super(ArrayTable.access$500(var1), nullptr);
      this.this$0 = var1;
      this.rowIndex = rowIndex;
   }

    std::string getKeyRole() {
      return "Column";
   }

    V getValue(int index) {
      return (V)this.this$0.at(this.rowIndex, index);
   }

    V setValue(int index, V newValue) {
      return (V)this.this$0.set(this.rowIndex, index, newValue);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
