#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class AbstractIdleService {
public:
   AbstractIdleService$1(AbstractIdleService var1) {
      this.this$0 = var1;
   }

    void execute(Runnable command) {
      MoreExecutors.newThread((std::string)AbstractIdleService.access$200(this.this$0).get(), command).start();
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
