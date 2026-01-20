#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/WellBehavedMap/EntrySet/1.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class WellBehavedMap {
public:
   WellBehavedMap$EntrySet$1$1(1 var1, Object var2) {
      this.this$2 = var1;
      this.val$key = var2;
   }

    K getKey() {
      return (K)this.val$key;
   }

    V getValue() {
      return (V)this.this$2.this$1.this$0.get(this.val$key);
   }

    V setValue(V value) {
      return (V)this.this$2.this$1.this$0.put(this.val$key, value);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
