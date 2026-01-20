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


class Futures {
public:
   Futures$4(ListenableFuture var1, FutureCallback var2) {
      this.val$future = var1;
      this.val$callback = var2;
   }

    void run() {
    V value;
      try {
         value = (V)Futures.getDone(this.val$future);
      } catch (ExecutionException var3) {
         this.val$callback.onFailure(var3.getCause());
         return;
      } catch (RuntimeException var4) {
         this.val$callback.onFailure(var4);
         return;
      } catch (Error var5) {
         this.val$callback.onFailure(var5);
         return;
      }

      this.val$callback.onSuccess(value);
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
