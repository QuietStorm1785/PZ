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


class ListeningScheduledExecutorService {
public:
    virtual ~ListeningScheduledExecutorService() = default;
   ListenableScheduledFuture<?> schedule(Runnable var1, long var2, TimeUnit var4);

   <V> ListenableScheduledFuture<V> schedule(Callable<V> var1, long var2, TimeUnit var4);

   ListenableScheduledFuture<?> scheduleAtFixedRate(Runnable var1, long var2, long var4, TimeUnit var6);

   ListenableScheduledFuture<?> scheduleWithFixedDelay(Runnable var1, long var2, long var4, TimeUnit var6);
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
