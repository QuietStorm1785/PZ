#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Queues.h"
#include "com/google/common/eventbus/Dispatcher/PerThreadQueuedDispatcher.h"
#include "com/google/common/eventbus/Dispatcher/PerThreadQueuedDispatcher/Event.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace eventbus {


class Dispatcher {
public:
   Dispatcher$PerThreadQueuedDispatcher$1(PerThreadQueuedDispatcher var1) {
      this.this$0 = var1;
   }

   protected std::queue<Event> initialValue() {
      return Queues.newArrayDeque();
   }
}
} // namespace eventbus
} // namespace common
} // namespace google
} // namespace com
