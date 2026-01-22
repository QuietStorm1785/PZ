#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace eventbus {


class Dispatcher {
public:
    const void* event;
   private const Iterator<Subscriber> subscribers;

   private Dispatcher$PerThreadQueuedDispatcher$Event(Object event, Iterator<Subscriber> subscribers) {
      this.event = event;
      this.subscribers = subscribers;
   }
}
} // namespace eventbus
} // namespace common
} // namespace google
} // namespace com
