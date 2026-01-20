#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"

namespace com {
namespace google {
namespace common {
namespace eventbus {


class SubscriberExceptionContext {
public:
    const EventBus eventBus;
    const void* event;
    const void* subscriber;
    const Method subscriberMethod;

   SubscriberExceptionContext(EventBus eventBus, Object event, Object subscriber, Method subscriberMethod) {
      this.eventBus = (EventBus)Preconditions.checkNotNull(eventBus);
      this.event = Preconditions.checkNotNull(event);
      this.subscriber = Preconditions.checkNotNull(subscriber);
      this.subscriberMethod = (Method)Preconditions.checkNotNull(subscriberMethod);
   }

    EventBus getEventBus() {
      return this.eventBus;
   }

    void* getEvent() {
      return this.event;
   }

    void* getSubscriber() {
      return this.subscriber;
   }

    Method getSubscriberMethod() {
      return this.subscriberMethod;
   }
}
} // namespace eventbus
} // namespace common
} // namespace google
} // namespace com
