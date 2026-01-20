#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Function.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class AbstractCatchingFuture {
public:
   AbstractCatchingFuture$CatchingFuture(ListenableFuture<? : public V> input, Class<X> exceptionType, Function<? super X, ? : public V> fallback) {
      super(input, exceptionType, fallback);
   }

    V doFallback(Function<? super, ? extends, X cause) {
      return (V)fallback.apply(cause);
   }

    void setResult(@Nullable V) {
      this.set(result);
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
