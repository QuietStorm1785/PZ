#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/ListenerCallQueue/Callback.h"
#include "com/google/common/util/concurrent/Service/Listener.h"
#include "com/google/common/util/concurrent/Service/State.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class AbstractService {
public:
   AbstractService$5(AbstractService var1, std::string x0, State var3, Throwable var4) {
      super(x0);
      this.this$0 = var1;
      this.val$from = var3;
      this.val$cause = var4;
   }

    void call(Listener listener) {
      listener.failed(this.val$from, this.val$cause);
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
