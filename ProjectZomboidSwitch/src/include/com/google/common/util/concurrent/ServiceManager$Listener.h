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


class ServiceManager {
public:
    void healthy() {
   }

    void stopped() {
   }

    void failure(Service service) {
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
