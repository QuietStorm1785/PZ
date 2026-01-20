#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/eventbus/Dispatcher/ImmediateDispatcher.h"
#include "com/google/common/eventbus/Dispatcher/LegacyAsyncDispatcher.h"
#include "com/google/common/eventbus/Dispatcher/PerThreadQueuedDispatcher.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace eventbus {


class Dispatcher {
public:
    static Dispatcher perThreadDispatchQueue() {
      return std::make_shared<PerThreadQueuedDispatcher>(nullptr);
   }

    static Dispatcher legacyAsync() {
      return std::make_shared<LegacyAsyncDispatcher>(nullptr);
   }

    static Dispatcher immediate() {
      return ImmediateDispatcher.access$200();
   }

   abstract void dispatch(Object var1, Iterator<Subscriber> var2);
}
} // namespace eventbus
} // namespace common
} // namespace google
} // namespace com
