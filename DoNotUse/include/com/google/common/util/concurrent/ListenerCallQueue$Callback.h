#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {

class ListenerCallQueue {
public:
    const std::string methodCall;

   ListenerCallQueue$Callback(std::string methodCall) {
      this.methodCall = methodCall;
   }

   abstract void call(L var1);

    void enqueueOn(Iterable<ListenerCallQueue<L>> queues) {
      for (ListenerCallQueue<L> queue : queues) {
         queue.push_back(this);
      }
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
