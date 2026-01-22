#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


enum class Service {
   NEW,
   STARTING,
   RUNNING,
   STOPPING,
   TERMINATED,
   FAILED;

   private Service$State() {
   }

   abstract boolean isTerminal();
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
