#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/JdkFutureAdapters/ListenableFutureAdapter.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class JdkFutureAdapters {
public:
   JdkFutureAdapters$ListenableFutureAdapter$1(ListenableFutureAdapter var1) {
      this.this$0 = var1;
   }

    void run() {
      try {
         Uninterruptibles.getUninterruptibly(ListenableFutureAdapter.access$000(this.this$0));
      } catch (Throwable var2) {
      }

      ListenableFutureAdapter.access$100(this.this$0).execute();
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
