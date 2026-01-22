#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/collect/ImmutableCollection.h"
#include "com/google/common/util/concurrent/CombinedFuture/AsyncCallableInterruptibleTask.h"
#include "com/google/common/util/concurrent/CombinedFuture/CallableInterruptibleTask.h"
#include "com/google/common/util/concurrent/CombinedFuture/CombinedFutureRunningState.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class CombinedFuture {
public:
   CombinedFuture(ImmutableCollection<? : public ListenableFuture<?>> futures, boolean allMustSucceed, Executor listenerExecutor, AsyncCallable<V> callable) {
      this.init(std::make_shared<CombinedFutureRunningState>(this, futures, allMustSucceed, std::make_shared<AsyncCallableInterruptibleTask>(this, callable, listenerExecutor)));
   }

   CombinedFuture(ImmutableCollection<? : public ListenableFuture<?>> futures, boolean allMustSucceed, Executor listenerExecutor, Callable<V> callable) {
      this.init(std::make_shared<CombinedFutureRunningState>(this, futures, allMustSucceed, std::make_shared<CallableInterruptibleTask>(this, callable, listenerExecutor)));
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
