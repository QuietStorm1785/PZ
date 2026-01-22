#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class AbstractFuture {
public:
    const bool wasInterrupted;
    const std::exception cause;

   AbstractFuture$Cancellation(boolean wasInterrupted, @Nullable Throwable cause) {
      this.wasInterrupted = wasInterrupted;
      this.cause = cause;
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
