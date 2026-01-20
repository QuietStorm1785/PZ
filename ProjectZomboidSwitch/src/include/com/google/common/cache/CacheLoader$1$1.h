#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/cache/CacheLoader/1.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace cache {


class CacheLoader {
public:
   CacheLoader$1$1(1 var1, Object var2, Object var3) {
      this.this$0 = var1;
      this.val$key = var2;
      this.val$oldValue = var3;
   }

    V call() {
      return (V)this.this$0.val$loader.reload(this.val$key, this.val$oldValue).get();
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
