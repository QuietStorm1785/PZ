#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/util/concurrent/Service/State.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class Service {
public:
    void starting() {
   }

    void running() {
   }

    void stopping(State from) {
   }

    void terminated(State from) {
   }

    void failed(State from, std::exception failure) {
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
