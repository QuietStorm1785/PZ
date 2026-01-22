#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/AbstractFuture/Listener.h"
#include "com/google/common/util/concurrent/AbstractFuture/Waiter.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class AbstractFuture {
public:
   private AbstractFuture$AtomicHelper() {
   }

   abstract void putThread(Waiter var1, Thread var2);

   abstract void putNext(Waiter var1, Waiter var2);

   abstract boolean casWaiters(AbstractFuture<?> var1, Waiter var2, Waiter var3);

   abstract boolean casListeners(AbstractFuture<?> var1, Listener var2, Listener var3);

   abstract boolean casValue(AbstractFuture<?> var1, Object var2, Object var3);
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
