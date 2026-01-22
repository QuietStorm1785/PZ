#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/ArrayTable/1/1.h"
#include "com/google/common/collect/Table/Cell.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class ArrayTable {
public:
   ArrayTable$1(ArrayTable var1, int x0) {
      super(x0);
      this.this$0 = var1;
   }

   protected Cell<R, C, V> get(int index) {
      return std::make_shared<1>(this, index);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
