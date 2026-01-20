#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/base/MoreObjects.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/eventbus/EventBus/LoggingHandler.h"
#include "com/google/common/util/concurrent/MoreExecutors.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace eventbus {


class EventBus {
public:
    static const Logger logger = Logger.getLogger(EventBus.class.getName());
    const std::string identifier;
    const Executor executor;
    const SubscriberExceptionHandler exceptionHandler;
    const SubscriberRegistry subscribers = std::make_shared<SubscriberRegistry>(this);
    const Dispatcher dispatcher;

    public EventBus() {
      this("default");
   }

    public EventBus(const std::string& identifier) {
      this(identifier, MoreExecutors.directExecutor(), Dispatcher.perThreadDispatchQueue(), LoggingHandler.INSTANCE);
   }

    public EventBus(SubscriberExceptionHandler exceptionHandler) {
      this("default", MoreExecutors.directExecutor(), Dispatcher.perThreadDispatchQueue(), exceptionHandler);
   }

   EventBus(std::string identifier, Executor executor, Dispatcher dispatcher, SubscriberExceptionHandler exceptionHandler) {
      this.identifier = (std::string)Preconditions.checkNotNull(identifier);
      this.executor = (Executor)Preconditions.checkNotNull(executor);
      this.dispatcher = (Dispatcher)Preconditions.checkNotNull(dispatcher);
      this.exceptionHandler = (SubscriberExceptionHandler)Preconditions.checkNotNull(exceptionHandler);
   }

    std::string identifier() {
      return this.identifier;
   }

    Executor executor() {
      return this.executor;
   }

    void handleSubscriberException(std::exception e, SubscriberExceptionContext context) {
      Preconditions.checkNotNull(e);
      Preconditions.checkNotNull(context);

      try {
         this.exceptionHandler.handleException(e, context);
      } catch (Throwable var4) {
         logger.log(Level.SEVERE, std::string.format(Locale.ROOT, "Exception %s thrown while handling exception: %s", var4, e), var4);
      }
   }

    void register(void* object) {
      this.subscribers.register(object);
   }

    void unregister(void* object) {
      this.subscribers.unregister(object);
   }

    void post(void* event) {
      Iterator<Subscriber> eventSubscribers = this.subscribers.getSubscribers(event);
      if (eventSubscribers.hasNext()) {
         this.dispatcher.dispatch(event, eventSubscribers);
      } else if (!(dynamic_cast<DeadEvent*>(event) != nullptr)) {
         this.post(std::make_shared<DeadEvent>(this, event));
      }
   }

    std::string toString() {
      return MoreObjects.toStringHelper(this).addValue(this.identifier);
   }
}
} // namespace eventbus
} // namespace common
} // namespace google
} // namespace com
