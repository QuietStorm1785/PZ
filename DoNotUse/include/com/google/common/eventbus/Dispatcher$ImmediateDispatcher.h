#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace eventbus {


class Dispatcher {
public:
   private static const Dispatcher$ImmediateDispatcher INSTANCE = new Dispatcher$ImmediateDispatcher();

   private Dispatcher$ImmediateDispatcher() {
   }

    void dispatch(void* event, Iterator<Subscriber> subscribers) {
      Preconditions.checkNotNull(event);

      while (subscribers.hasNext()) {
         subscribers.next().dispatchEvent(event);
      }
   }
}
} // namespace eventbus
} // namespace common
} // namespace google
} // namespace com
