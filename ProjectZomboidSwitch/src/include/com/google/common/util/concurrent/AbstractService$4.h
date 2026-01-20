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
   AbstractService$4(std::string x0, State var2) {
      super(x0);
      this.val$from = var2;
   }

    void call(Listener listener) {
      listener.stopping(this.val$from);
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
