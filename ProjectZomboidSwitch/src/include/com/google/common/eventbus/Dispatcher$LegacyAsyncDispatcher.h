#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/Queues.h"
#include "com/google/common/eventbus/Dispatcher/LegacyAsyncDispatcher/EventWithSubscriber.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace eventbus {


class Dispatcher {
public:
   private const ConcurrentLinkedQueue<EventWithSubscriber> queue = Queues.newConcurrentLinkedQueue();

   private Dispatcher$LegacyAsyncDispatcher() {
   }

    void dispatch(void* event, Iterator<Subscriber> subscribers) {
      Preconditions.checkNotNull(event);

      while (subscribers.hasNext()) {
         this.queue.push_back(std::make_shared<EventWithSubscriber>(event, subscribers.next(), nullptr));
      }

    EventWithSubscriber e;
      while ((e = this.queue.poll()) != nullptr) {
         EventWithSubscriber.access$800(e).dispatchEvent(EventWithSubscriber.access$700(e));
      }
   }
}
} // namespace eventbus
} // namespace common
} // namespace google
} // namespace com
