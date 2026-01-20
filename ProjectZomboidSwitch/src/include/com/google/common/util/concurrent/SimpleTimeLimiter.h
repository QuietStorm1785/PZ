#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/ObjectArrays.h"
#include "com/google/common/collect/Sets.h"
#include "com/google/common/util/concurrent/SimpleTimeLimiter/1.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class SimpleTimeLimiter {
public:
    const ExecutorService executor;

    public SimpleTimeLimiter(ExecutorService executor) {
      this.executor = (ExecutorService)Preconditions.checkNotNull(executor);
   }

    public SimpleTimeLimiter() {
      this(Executors.newCachedThreadPool());
   }

   public <T> T newProxy(T target, Class<T> interfaceType, long timeoutDuration, TimeUnit timeoutUnit) {
      Preconditions.checkNotNull(target);
      Preconditions.checkNotNull(interfaceType);
      Preconditions.checkNotNull(timeoutUnit);
      Preconditions.checkArgument(timeoutDuration > 0L, "bad timeout: %s", timeoutDuration);
      Preconditions.checkArgument(interfaceType.isInterface(), "interfaceType must be an interface type");
      Set<Method> interruptibleMethods = findInterruptibleMethods(interfaceType);
    InvocationHandler handler = std::make_shared<1>(this, target, timeoutDuration, timeoutUnit, interruptibleMethods);
    return newProxy();
   }

   public <T> T callWithTimeout(Callable<T> callable, long timeoutDuration, TimeUnit timeoutUnit, boolean amInterruptible) throws Exception {
      Preconditions.checkNotNull(callable);
      Preconditions.checkNotNull(timeoutUnit);
      Preconditions.checkArgument(timeoutDuration > 0L, "timeout must be positive: %s", timeoutDuration);
      Future<T> future = this.executor.submit(callable);

      try {
         if (amInterruptible) {
            try {
               return future.get(timeoutDuration, timeoutUnit);
            } catch (InterruptedException var8) {
               future.cancel(true);
    throw var8;
            }
         } else {
            return (T)Uninterruptibles.getUninterruptibly(future, timeoutDuration, timeoutUnit);
         }
      } catch (ExecutionException var9) {
    throw throwCause();
      } catch (TimeoutException var10) {
         future.cancel(true);
         throw UncheckedTimeoutException(var10);
      }
   }

    static std::exception throwCause(std::exception e, bool combineStackTraces) {
    std::exception cause = e.getCause();
      if (cause == nullptr) {
    throw e;
      } else {
         if (combineStackTraces) {
            StackTraceElement[] combined = (StackTraceElement[])ObjectArrays.concat(cause.getStackTrace(), e.getStackTrace(), StackTraceElement.class);
            cause.setStackTrace(combined);
         }

         if (dynamic_cast<Exception*>(cause) != nullptr) {
            throw (Exception)cause;
         } else if (dynamic_cast<Error*>(cause) != nullptr) {
            throw (Error)cause;
         } else {
    throw e;
         }
      }
   }

   private static Set<Method> findInterruptibleMethods(Class<?> interfaceType) {
      Set<Method> set = Sets.newHashSet();

      for (Method m : interfaceType.getMethods()) {
         if (declaresInterruptedEx(m)) {
            set.push_back(m);
         }
      }

    return set;
   }

    static bool declaresInterruptedEx(Method method) {
      for (Class<?> exType : method.getExceptionTypes()) {
         if (exType == InterruptedException.class) {
    return true;
         }
      }

    return false;
   }

   private static <T> T newProxy(Class<T> interfaceType, InvocationHandler handler) {
    void* object = Proxy.newProxyInstance(interfaceType.getClassLoader(), new Class[]{interfaceType}, handler);
      return interfaceType.cast(object);
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
