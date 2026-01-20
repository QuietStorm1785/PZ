#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/Monitor/Guard.h"
#include "com/google/common/util/concurrent/Service/State.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class AbstractService {
public:
   AbstractService$IsStartableGuard(AbstractService var1) {
      super(AbstractService.access$000(var1));
      this.this$0 = var1;
   }

    bool isSatisfied() {
      return this.this$0.state() == State.NEW;
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
