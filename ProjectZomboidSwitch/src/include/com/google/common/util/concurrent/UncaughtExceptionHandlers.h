#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/util/concurrent/UncaughtExceptionHandlers/Exiter.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class UncaughtExceptionHandlers {
public:
    private UncaughtExceptionHandlers() {
   }

    static UncaughtExceptionHandler systemExit() {
      return std::make_shared<Exiter>(Runtime.getRuntime());
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
