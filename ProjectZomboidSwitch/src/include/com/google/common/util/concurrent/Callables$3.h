#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Supplier.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class Callables {
public:
   Callables$3(Supplier var1, Callable var2) {
      this.val$nameSupplier = var1;
      this.val$callable = var2;
   }

    T call() {
    Thread currentThread = Thread.currentThread();
    std::string oldName = currentThread.getName();
    bool restoreName = Callables.access$000((std::string)this.val$nameSupplier.get(), currentThread);

    void* var4;
      try {
         var4 = this.val$callable.call();
      } finally {
         if (restoreName) {
    bool unused = Callables.access$000(oldName, currentThread);
         }
      }

      return (T)var4;
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
