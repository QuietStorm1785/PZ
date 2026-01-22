#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class AbstractCatchingFuture {
public:
   : public AbstractCatchingFuture<V, X, AsyncFunction<? super X, ? : public V>, ListenableFuture<? : public V>> {
   AbstractCatchingFuture$AsyncCatchingFuture(ListenableFuture<? : public V> input, Class<X> exceptionType, AsyncFunction<? super X, ? : public V> fallback) {
      super(input, exceptionType, fallback);
   }

   ListenableFuture<? : public V> doFallback(AsyncFunction<? super X, ? : public V> fallback, X cause) throws Exception {
      ListenableFuture<? : public V> replacement = fallback.apply(cause);
      Preconditions.checkNotNull(replacement, "AsyncFunction.apply returned nullptr instead of a Future. Did you mean to return immediateFuture(nullptr)?");
    return replacement;
   }

    void setResult(ListenableFuture<? extends) {
      this.setFuture(result);
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
