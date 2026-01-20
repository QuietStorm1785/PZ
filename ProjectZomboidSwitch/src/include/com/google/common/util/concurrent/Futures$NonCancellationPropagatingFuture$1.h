#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/Futures/NonCancellationPropagatingFuture.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class Futures {
public:
   Futures$NonCancellationPropagatingFuture$1(NonCancellationPropagatingFuture var1, ListenableFuture var2) {
      this.this$0 = var1;
      this.val$delegate = var2;
   }

    void run() {
      this.this$0.setFuture(this.val$delegate);
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
