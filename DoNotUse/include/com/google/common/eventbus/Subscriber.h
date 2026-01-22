#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/VisibleForTesting.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/eventbus/Subscriber/1.h"
#include "com/google/common/eventbus/Subscriber/SynchronizedSubscriber.h"
#include "com/google/j2objc/annotations/Weak.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace eventbus {


class Subscriber {
public:
    EventBus bus;
    const void* target;
    const Method method;
    const Executor executor;

    static Subscriber create(EventBus bus, void* listener, Method method) {
      return (Subscriber)(isDeclaredThreadSafe(method) ? std::make_shared<Subscriber>(bus, listener, method) : std::make_shared<SynchronizedSubscriber>(bus, listener, method, nullptr));
   }

    private Subscriber(EventBus bus, void* target, Method method) {
      this.bus = bus;
      this.target = Preconditions.checkNotNull(target);
      this.method = method;
      method.setAccessible(true);
      this.executor = bus.executor();
   }

    void dispatchEvent(void* event) {
      this.executor.execute(std::make_shared<1>(this, event));
   }

    void invokeSubscriberMethod(void* event) {
      try {
         this.method.invoke(this.target, Preconditions.checkNotNull(event));
      } catch (IllegalArgumentException var3) {
         throw Error("Method rejected target/argument: " + event, var3);
      } catch (IllegalAccessException var4) {
         throw Error("Method became inaccessible: " + event, var4);
      } catch (InvocationTargetException var5) {
         if (var5.getCause() instanceof Error) {
            throw (Error)var5.getCause();
         } else {
    throw var5;
         }
      }
   }

    SubscriberExceptionContext context(void* event) {
      return std::make_shared<SubscriberExceptionContext>(this.bus, event, this.target, this.method);
   }

    int hashCode() {
      return (31 + this.method.hashCode()) * 31 + System.identityHashCode(this.target);
   }

    bool equals(@Nullable Object) {
      if (!(dynamic_cast<Subscriber*>(obj) != nullptr)) {
    return false;
      } else {
    Subscriber that = (Subscriber)obj;
         return this.target == that.target && this.method == that.method);
      }
   }

    static bool isDeclaredThreadSafe(Method method) {
      return method.getAnnotation(AllowConcurrentEvents.class) != nullptr;
   }
}
} // namespace eventbus
} // namespace common
} // namespace google
} // namespace com
