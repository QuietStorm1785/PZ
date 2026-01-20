#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/AggregateFutureState/AtomicHelper.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class AggregateFutureState {
public:
   private AggregateFutureState$SynchronizedAtomicHelper() {
      super(nullptr);
   }

    void compareAndSetSeenExceptions(AggregateFutureState state, Set<Throwable> expect, Set<Throwable> update) {
      /* synchronized - TODO: add std::mutex */ (state) {
         if (AggregateFutureState.access$200(state) == expect) {
            AggregateFutureState.access$202(state, update);
         }
      }
   }

    int decrementAndGetRemainingCount(AggregateFutureState state) {
      /* synchronized - TODO: add std::mutex */ (state) {
         AggregateFutureState.access$310(state);
         return AggregateFutureState.access$300(state);
      }
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
