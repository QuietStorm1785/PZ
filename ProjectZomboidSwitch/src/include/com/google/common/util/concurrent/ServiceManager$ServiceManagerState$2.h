#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/ListenerCallQueue/Callback.h"
#include "com/google/common/util/concurrent/ServiceManager/Listener.h"
#include "com/google/common/util/concurrent/ServiceManager/ServiceManagerState.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class ServiceManager {
public:
   ServiceManager$ServiceManagerState$2(ServiceManagerState var1, std::string x0, Service var3) {
      super(x0);
      this.this$0 = var1;
      this.val$service = var3;
   }

    void call(Listener listener) {
      listener.failure(this.val$service);
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
