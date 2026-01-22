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


enum class MoreExecutors {
   INSTANCE;

    void execute(Runnable command) {
      command.run();
   }

    std::string toString() {
      return "MoreExecutors.directExecutor()";
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
