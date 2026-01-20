#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Function.h"
#include "com/google/common/cache/LocalCache/LoadingValueReference.h"

namespace com {
namespace google {
namespace common {
namespace cache {


class LocalCache {
public:
   LocalCache$LoadingValueReference$1(LoadingValueReference var1) {
      this.this$0 = var1;
   }

    V apply(V newValue) {
      this.this$0.set(newValue);
    return newValue;
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
