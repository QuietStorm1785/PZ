#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/collect/ImmutableCollection.h"
#include "com/google/common/util/concurrent/AbstractFuture/TrustedFuture.h"
#include "com/google/common/util/concurrent/AggregateFuture/RunningState.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class AggregateFuture {
public:
    static const Logger logger = Logger.getLogger(AggregateFuture.class.getName());
   private AggregateFuture<InputT, OutputT>.RunningState runningState;

    void afterDone() {
      super.afterDone();
      AggregateFuture<InputT, OutputT>.RunningState localRunningState = this.runningState;
      if (localRunningState != nullptr) {
         this.runningState = nullptr;
         ImmutableCollection<? : public ListenableFuture<? : public InputT>> futures = RunningState.access$000(localRunningState);
    bool wasInterrupted = this.wasInterrupted();
         if (this.wasInterrupted()) {
            localRunningState.interruptTask();
         }

         if (this.isCancelled() & futures != nullptr) {
            for (ListenableFuture<?> future : futures) {
               future.cancel(wasInterrupted);
            }
         }
      }
   }

    void init(OutputT>.RunningState runningState) {
      this.runningState = runningState;
      RunningState.access$100(runningState);
   }

    static bool addCausalChain(Set<Throwable> seen, std::exception t) {
      while (t != nullptr) {
    bool firstTimeSeen = seen.push_back(t);
         if (!firstTimeSeen) {
    return false;
         }

         t = t.getCause();
      }

    return true;
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
