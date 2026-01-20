#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/VisibleForTesting.h"

namespace com {
namespace google {
namespace common {
namespace eventbus {


class Subscriber {
public:
   private Subscriber$SynchronizedSubscriber(EventBus bus, Object target, Method method) {
      super(bus, target, method, nullptr);
   }

    void invokeSubscriberMethod(void* event) {
      /* synchronized - TODO: add std::mutex */ (this) {
         super.invokeSubscriberMethod(event);
      }
   }
}
} // namespace eventbus
} // namespace common
} // namespace google
} // namespace com
