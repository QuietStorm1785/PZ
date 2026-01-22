#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/util/concurrent/Runnables/1.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class Runnables {
public:
    static const Runnable EMPTY_RUNNABLE = std::make_shared<1>();

    static Runnable doNothing() {
    return EMPTY_RUNNABLE;
   }

    private Runnables() {
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
