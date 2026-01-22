#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/eventbus/Dispatcher/PerThreadQueuedDispatcher/1.h"
#include "com/google/common/eventbus/Dispatcher/PerThreadQueuedDispatcher/2.h"
#include "com/google/common/eventbus/Dispatcher/PerThreadQueuedDispatcher/Event.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace eventbus {


class Dispatcher {
public:
   private const ThreadLocal<std::queue<Event>> queue = std::make_shared<1>(this);
   private const ThreadLocal<bool> dispatching = std::make_shared<2>(this);

   private Dispatcher$PerThreadQueuedDispatcher() {
   }

    void dispatch(void* event, Iterator<Subscriber> subscribers) {
      Preconditions.checkNotNull(event);
      Preconditions.checkNotNull(subscribers);
      std::queue<Event> queueForThread = this.queue.get();
      queueForThread.offer(std::make_shared<Event>(event, subscribers, nullptr));
      if (!this.dispatching.get()) {
         this.dispatching.set(true);

    Event nextEvent;
         try {
            while ((nextEvent = queueForThread.poll()) != nullptr) {
               while (Event.access$400(nextEvent).hasNext()) {
                  ((Subscriber)Event.access$400(nextEvent).next()).dispatchEvent(Event.access$500(nextEvent));
               }
            }
         } finally {
            this.dispatching.remove();
            this.queue.remove();
         }
      }
   }
}
} // namespace eventbus
} // namespace common
} // namespace google
} // namespace com
