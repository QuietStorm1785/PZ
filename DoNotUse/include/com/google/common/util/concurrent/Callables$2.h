#pragma once
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


class Callables {
public:
   Callables$2(ListeningExecutorService var1, Callable var2) {
      this.val$listeningExecutorService = var1;
      this.val$callable = var2;
   }

   public ListenableFuture<T> call() throws Exception {
      return this.val$listeningExecutorService.submit(this.val$callable);
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
