#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/AbstractFuture/TrustedFuture.h"
#include "com/google/common/util/concurrent/Futures/NonCancellationPropagatingFuture/1.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class Futures {
public:
   Futures$NonCancellationPropagatingFuture(ListenableFuture<V> delegate) {
      delegate.addListener(std::make_shared<1>(this, delegate), MoreExecutors.directExecutor());
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
