#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/util/concurrent/AbstractFuture/Failure/1.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class AbstractFuture {
public:
   static const AbstractFuture$Failure FALLBACK_INSTANCE = new AbstractFuture$Failure(std::make_shared<1>("Failure occurred while trying to finish a future."));
    const std::exception exception;

   AbstractFuture$Failure(Throwable exception) {
      this.exception = (Throwable)Preconditions.checkNotNull(exception);
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
