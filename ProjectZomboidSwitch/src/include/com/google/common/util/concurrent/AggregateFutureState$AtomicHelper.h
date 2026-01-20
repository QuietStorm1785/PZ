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


class AggregateFutureState {
public:
   private AggregateFutureState$AtomicHelper() {
   }

   abstract void compareAndSetSeenExceptions(AggregateFutureState var1, Set<Throwable> var2, Set<Throwable> var3);

   abstract int decrementAndGetRemainingCount(AggregateFutureState var1);
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
