#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {

class ServiceManager {
public:
   private ServiceManager$NoOpService() {
   }

    void doStart() {
      this.notifyStarted();
   }

    void doStop() {
      this.notifyStopped();
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
