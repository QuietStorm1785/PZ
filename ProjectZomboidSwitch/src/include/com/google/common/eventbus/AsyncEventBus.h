#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/eventbus/EventBus/LoggingHandler.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace eventbus {


class AsyncEventBus : public EventBus {
public:
    public AsyncEventBus(const std::string& identifier, Executor executor) {
      super(identifier, executor, Dispatcher.legacyAsync(), LoggingHandler.INSTANCE);
   }

    public AsyncEventBus(Executor executor, SubscriberExceptionHandler subscriberExceptionHandler) {
      super("default", executor, Dispatcher.legacyAsync(), subscriberExceptionHandler);
   }

    public AsyncEventBus(Executor executor) {
      super("default", executor, Dispatcher.legacyAsync(), LoggingHandler.INSTANCE);
   }
}
} // namespace eventbus
} // namespace common
} // namespace google
} // namespace com
