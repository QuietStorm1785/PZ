#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/cache/LocalCache/LocalManualCache.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace cache {


class LocalCache {
public:
   LocalCache$LocalManualCache$1(LocalManualCache var1, Callable var2) {
      this.this$0 = var1;
      this.val$valueLoader = var2;
   }

    V load(void* key) {
      return (V)this.val$valueLoader.call();
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
