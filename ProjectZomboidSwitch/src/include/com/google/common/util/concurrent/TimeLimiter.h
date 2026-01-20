#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class TimeLimiter {
public:
    virtual ~TimeLimiter() = default;
   <T> T newProxy(T var1, Class<T> var2, long var3, TimeUnit var5);

   <T> T callWithTimeout(Callable<T> var1, long var2, TimeUnit var4, boolean var5) throws Exception;
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
