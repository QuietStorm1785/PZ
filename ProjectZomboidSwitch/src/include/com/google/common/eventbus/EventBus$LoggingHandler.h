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
namespace eventbus {


class EventBus {
public:
   static const EventBus$LoggingHandler INSTANCE = new EventBus$LoggingHandler();

    void handleException(std::exception exception, SubscriberExceptionContext context) {
    Logger logger = logger(context);
      if (logger.isLoggable(Level.SEVERE)) {
         logger.log(Level.SEVERE, message(context), exception);
      }
   }

    static Logger logger(SubscriberExceptionContext context) {
      return Logger.getLogger(EventBus.class.getName() + "." + context.getEventBus().identifier());
   }

    static std::string message(SubscriberExceptionContext context) {
    Method method = context.getSubscriberMethod();
      return "Exception thrown by subscriber method "
         + method.getName()
         + '('
         + method.getParameterTypes()[0].getName()
         + ')'
         + " on subscriber "
         + context.getSubscriber()
         + " when dispatching event: "
         + context.getEvent();
   }
}
} // namespace eventbus
} // namespace common
} // namespace google
} // namespace com
