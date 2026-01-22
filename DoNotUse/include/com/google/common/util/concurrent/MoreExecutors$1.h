#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class MoreExecutors {
public:
   MoreExecutors$1(BlockingQueue var1, ListenableFuture var2) {
      this.val$queue = var1;
      this.val$future = var2;
   }

    void run() {
      this.val$queue.push_back(this.val$future);
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
