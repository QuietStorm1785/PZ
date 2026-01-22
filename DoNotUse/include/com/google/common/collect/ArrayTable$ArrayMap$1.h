#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/ArrayTable/ArrayMap.h"
#include "com/google/common/collect/ArrayTable/ArrayMap/1/1.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class ArrayTable {
public:
   ArrayTable$ArrayMap$1(ArrayMap var1, int x0) {
      super(x0);
      this.this$0 = var1;
   }

   protected Entry<K, V> get(int index) {
      return std::make_shared<1>(this, index);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
