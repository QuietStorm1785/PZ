#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/cache/RemovalListeners/1.h"

namespace com {
namespace google {
namespace common {
namespace cache {


class RemovalListeners {
public:
   RemovalListeners$1$1(1 var1, RemovalNotification var2) {
      this.this$0 = var1;
      this.val$notification = var2;
   }

    void run() {
      this.this$0.val$listener.onRemoval(this.val$notification);
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
