#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/AggregateFuture/RunningState.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class AggregateFuture {
public:
   AggregateFuture$RunningState$1(RunningState var1, int var2, ListenableFuture var3) {
      this.this$1 = var1;
      this.val$index = var2;
      this.val$listenable = var3;
   }

    void run() {
      try {
         RunningState.access$200(this.this$1, this.val$index, this.val$listenable);
      } finally {
         RunningState.access$300(this.this$1);
      }
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
