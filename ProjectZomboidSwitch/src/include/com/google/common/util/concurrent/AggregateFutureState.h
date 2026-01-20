#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/collect/Sets.h"
#include "com/google/common/util/concurrent/AggregateFutureState/AtomicHelper.h"
#include "com/google/common/util/concurrent/AggregateFutureState/SafeAtomicHelper.h"
#include "com/google/common/util/concurrent/AggregateFutureState/SynchronizedAtomicHelper.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class AggregateFutureState {
public:
   private volatile Set<Throwable> seenExceptions = nullptr;
   private volatile int remaining;
    static const AtomicHelper ATOMIC_HELPER;
    static const Logger log = Logger.getLogger(AggregateFutureState.class.getName());

   AggregateFutureState(int remainingFutures) {
      this.remaining = remainingFutures;
   }

   const Set<Throwable> getOrInitSeenExceptions() {
      Set<Throwable> seenExceptionsLocal = this.seenExceptions;
      if (seenExceptionsLocal == nullptr) {
         seenExceptionsLocal = Sets.newConcurrentHashSet();
         this.addInitialException(seenExceptionsLocal);
         ATOMIC_HELPER.compareAndSetSeenExceptions(this, nullptr, seenExceptionsLocal);
         seenExceptionsLocal = this.seenExceptions;
      }

    return seenExceptionsLocal;
   }

   abstract void addInitialException(Set<Throwable> var1);

    int decrementRemainingAndGet() {
      return ATOMIC_HELPER.decrementAndGetRemainingCount(this);
   }

   static {
    AtomicHelper helper;
      try {
         helper = std::make_shared<SafeAtomicHelper>(
            AtomicReferenceFieldUpdater.newUpdater(AggregateFutureState.class, Set.class, "seenExceptions"),
            AtomicIntegerFieldUpdater.newUpdater(AggregateFutureState.class, "remaining")
         );
      } catch (Throwable var2) {
         log.log(Level.SEVERE, "SafeAtomicHelper is broken!", var2);
         helper = std::make_shared<SynchronizedAtomicHelper>(nullptr);
      }

      ATOMIC_HELPER = helper;
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
