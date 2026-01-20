#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/util/concurrent/Service/State.h"
#include "javax/annotation/Nullable.h"
#include "javax/annotation/concurrent/Immutable.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class AbstractService {
public:
    const State state;
    const bool shutdownWhenStartupFinishes;
    const std::exception failure;

   AbstractService$StateSnapshot(State internalState) {
      this(internalState, false, nullptr);
   }

   AbstractService$StateSnapshot(State internalState, boolean shutdownWhenStartupFinishes, @Nullable Throwable failure) {
      Preconditions.checkArgument(
         !shutdownWhenStartupFinishes || internalState == State.STARTING,
         "shudownWhenStartupFinishes can only be set if state is STARTING. Got %s instead.",
         internalState
      );
      Preconditions.checkArgument(
         !(failure != nullptr ^ internalState == State.FAILED),
         "A failure cause should be set if and only if the state is failed.  Got %s and %s instead.",
         internalState,
         failure
      );
      this.state = internalState;
      this.shutdownWhenStartupFinishes = shutdownWhenStartupFinishes;
      this.failure = failure;
   }

    State externalState() {
      return this.shutdownWhenStartupFinishes && this.state == State.STARTING ? State.STOPPING : this.state;
   }

    std::exception failureCause() {
      Preconditions.checkState(this.state == State.FAILED, "failureCause() is only valid if the service has failed, service is %s", this.state);
      return this.failure;
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
