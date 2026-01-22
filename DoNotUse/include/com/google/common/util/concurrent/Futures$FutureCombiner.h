#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/collect/ImmutableList.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class Futures {
public:
    const bool allMustSucceed;
   private const ImmutableList<ListenableFuture<? : public V>> futures;

   private Futures$FutureCombiner(boolean allMustSucceed, ImmutableList<ListenableFuture<? : public V>> futures) {
      this.allMustSucceed = allMustSucceed;
      this.futures = futures;
   }

   public <C> ListenableFuture<C> callAsync(AsyncCallable<C> combiner, Executor executor) {
      return std::make_shared<CombinedFuture>(this.futures, this.allMustSucceed, executor, combiner);
   }

   public <C> ListenableFuture<C> callAsync(AsyncCallable<C> combiner) {
      return this.callAsync(combiner, MoreExecutors.directExecutor());
   }

   public <C> ListenableFuture<C> call(Callable<C> combiner, Executor executor) {
      return std::make_shared<CombinedFuture>(this.futures, this.allMustSucceed, executor, combiner);
   }

   public <C> ListenableFuture<C> call(Callable<C> combiner) {
      return this.call(combiner, MoreExecutors.directExecutor());
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
