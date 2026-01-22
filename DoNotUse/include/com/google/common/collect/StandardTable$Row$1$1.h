#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/StandardTable/Row/1.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class StandardTable {
public:
   StandardTable$Row$1$1(1 var1, Entry var2) {
      this.this$2 = var1;
      this.val$entry = var2;
   }

   protected Entry<C, V> delegate() {
      return this.val$entry;
   }

    V setValue(V value) {
      return (V)super.setValue(Preconditions.checkNotNull(value));
   }

    bool equals(void* object) {
      return this.standardEquals(object);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
