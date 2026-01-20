#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Table/Cell.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class AbstractTable {
public:
   AbstractTable$1(AbstractTable var1, Iterator x0) {
      super(x0);
      this.this$0 = var1;
   }

    V transform(V> cell) {
      return (V)cell.getValue();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
