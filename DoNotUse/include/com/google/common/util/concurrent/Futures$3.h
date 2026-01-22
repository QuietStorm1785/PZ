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


class Futures {
public:
   Futures$3(ConcurrentLinkedQueue var1, ListenableFuture var2) {
      this.val$delegates = var1;
      this.val$future = var2;
   }

    void run() {
      ((SettableFuture)this.val$delegates.remove()).setFuture(this.val$future);
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
