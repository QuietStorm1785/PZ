#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/ListenerCallQueue/Callback.h"
#include "com/google/common/util/concurrent/Service/Listener.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class AbstractService {
public:
   AbstractService$2(std::string x0) {
      super(x0);
   }

    void call(Listener listener) {
      listener.running();
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
