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

class Dispatcher {
public:
    const void* event;
    const Subscriber subscriber;

   private Dispatcher$LegacyAsyncDispatcher$EventWithSubscriber(Object event, Subscriber subscriber) {
      this.event = event;
      this.subscriber = subscriber;
   }
}
} // namespace eventbus
} // namespace common
} // namespace google
} // namespace com
