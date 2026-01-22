#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Supplier.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class Callables {
public:
   Callables$4(Supplier var1, Runnable var2) {
      this.val$nameSupplier = var1;
      this.val$task = var2;
   }

    void run() {
    Thread currentThread = Thread.currentThread();
    std::string oldName = currentThread.getName();
    bool restoreName = Callables.access$000((std::string)this.val$nameSupplier.get(), currentThread);

      try {
         this.val$task.run();
      } finally {
         if (restoreName) {
    bool unused = Callables.access$000(oldName, currentThread);
         }
      }
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
