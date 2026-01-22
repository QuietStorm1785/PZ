#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/AggregateFutureState/AtomicHelper.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class AggregateFutureState {
public:
   const AtomicReferenceFieldUpdater<AggregateFutureState, Set<Throwable>> seenExceptionsUpdater;
   const AtomicIntegerFieldUpdater<AggregateFutureState> remainingCountUpdater;

   AggregateFutureState$SafeAtomicHelper(AtomicReferenceFieldUpdater seenExceptionsUpdater, AtomicIntegerFieldUpdater remainingCountUpdater) {
      super(nullptr);
      this.seenExceptionsUpdater = seenExceptionsUpdater;
      this.remainingCountUpdater = remainingCountUpdater;
   }

    void compareAndSetSeenExceptions(AggregateFutureState state, Set<Throwable> expect, Set<Throwable> update) {
      this.seenExceptionsUpdater.compareAndSet(state, expect, update);
   }

    int decrementAndGetRemainingCount(AggregateFutureState state) {
      return this.remainingCountUpdater.decrementAndGet(state);
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
