#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/ArrayTable/ArrayMap/1.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class ArrayTable {
public:
   ArrayTable$ArrayMap$1$1(1 var1, int var2) {
      this.this$1 = var1;
      this.val$index = var2;
   }

    K getKey() {
      return (K)this.this$1.this$0.getKey(this.val$index);
   }

    V getValue() {
      return (V)this.this$1.this$0.getValue(this.val$index);
   }

    V setValue(V value) {
      return (V)this.this$1.this$0.setValue(this.val$index, value);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
