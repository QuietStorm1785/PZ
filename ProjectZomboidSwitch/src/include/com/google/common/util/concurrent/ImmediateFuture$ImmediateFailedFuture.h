#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/AbstractFuture/TrustedFuture.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class ImmediateFuture {
public:
   ImmediateFuture$ImmediateFailedFuture(Throwable thrown) {
      this.setException(thrown);
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
