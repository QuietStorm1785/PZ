#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/util/concurrent/Service/Listener.h"
#include "com/google/common/util/concurrent/Service/State.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class Service {
public:
    virtual ~Service() = default;
    Service startAsync();

    bool isRunning();

    State state();

    Service stopAsync();

    void awaitRunning();

    void awaitRunning(long var1, TimeUnit var3);

    void awaitTerminated();

    void awaitTerminated(long var1, TimeUnit var3);

    std::exception failureCause();

    void addListener(Listener var1, Executor var2);
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
