#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/cache/RemovalListeners/1/1.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace cache {


class RemovalListeners {
public:
   RemovalListeners$1(Executor var1, RemovalListener var2) {
      this.val$executor = var1;
      this.val$listener = var2;
   }

    void onRemoval(V> notification) {
      this.val$executor.execute(std::make_shared<1>(this, notification));
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
