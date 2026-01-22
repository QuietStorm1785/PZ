#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/AbstractFuture/AtomicHelper.h"
#include "com/google/common/util/concurrent/AbstractFuture/Listener.h"
#include "com/google/common/util/concurrent/AbstractFuture/Waiter.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class AbstractFuture {
public:
   private AbstractFuture$SynchronizedHelper() {
      super(nullptr);
   }

    void putThread(Waiter waiter, Thread newValue) {
      waiter.thread = newValue;
   }

    void putNext(Waiter waiter, Waiter newValue) {
      waiter.next = newValue;
   }

    bool casWaiters(AbstractFuture<?> future, Waiter expect, Waiter update) {
      /* synchronized - TODO: add std::mutex */ (future) {
         if (AbstractFuture.access$700(future) == expect) {
            AbstractFuture.access$702(future, update);
    return true;
         } else {
    return false;
         }
      }
   }

    bool casListeners(AbstractFuture<?> future, Listener expect, Listener update) {
      /* synchronized - TODO: add std::mutex */ (future) {
         if (AbstractFuture.access$800(future) == expect) {
            AbstractFuture.access$802(future, update);
    return true;
         } else {
    return false;
         }
      }
   }

    bool casValue(AbstractFuture<?> future, void* expect, void* update) {
      /* synchronized - TODO: add std::mutex */ (future) {
         if (AbstractFuture.access$300(future) == expect) {
            AbstractFuture.access$302(future, update);
    return true;
         } else {
    return false;
         }
      }
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
