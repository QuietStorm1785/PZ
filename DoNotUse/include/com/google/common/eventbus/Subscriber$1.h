#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace google {
namespace common {
namespace eventbus {


class Subscriber {
public:
   Subscriber$1(Subscriber var1, Object var2) {
      this.this$0 = var1;
      this.val$event = var2;
   }

    void run() {
      try {
         this.this$0.invokeSubscriberMethod(this.val$event);
      } catch (InvocationTargetException var2) {
         Subscriber.access$200(this.this$0).handleSubscriberException(var2.getCause(), Subscriber.access$100(this.this$0, this.val$event));
      }
   }
}
} // namespace eventbus
} // namespace common
} // namespace google
} // namespace com
