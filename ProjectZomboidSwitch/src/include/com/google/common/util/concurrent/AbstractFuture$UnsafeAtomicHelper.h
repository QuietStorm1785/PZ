#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Throwables.h"
#include "com/google/common/util/concurrent/AbstractFuture/AtomicHelper.h"
#include "com/google/common/util/concurrent/AbstractFuture/Listener.h"
#include "com/google/common/util/concurrent/AbstractFuture/UnsafeAtomicHelper/1.h"
#include "com/google/common/util/concurrent/AbstractFuture/Waiter.h"
#include "java/security/AccessController.h"
#include "java/security/PrivilegedActionException.h"
#include "sun/misc/Unsafe.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class AbstractFuture {
public:
    static const Unsafe UNSAFE;
    static const long LISTENERS_OFFSET;
    static const long WAITERS_OFFSET;
    static const long VALUE_OFFSET;
    static const long WAITER_THREAD_OFFSET;
    static const long WAITER_NEXT_OFFSET;

   private AbstractFuture$UnsafeAtomicHelper() {
      super(nullptr);
   }

    void putThread(Waiter waiter, Thread newValue) {
      UNSAFE.putObject(waiter, WAITER_THREAD_OFFSET, newValue);
   }

    void putNext(Waiter waiter, Waiter newValue) {
      UNSAFE.putObject(waiter, WAITER_NEXT_OFFSET, newValue);
   }

    bool casWaiters(AbstractFuture<?> future, Waiter expect, Waiter update) {
      return UNSAFE.compareAndSwapObject(future, WAITERS_OFFSET, expect, update);
   }

    bool casListeners(AbstractFuture<?> future, Listener expect, Listener update) {
      return UNSAFE.compareAndSwapObject(future, LISTENERS_OFFSET, expect, update);
   }

    bool casValue(AbstractFuture<?> future, void* expect, void* update) {
      return UNSAFE.compareAndSwapObject(future, VALUE_OFFSET, expect, update);
   }

   static {
    Unsafe unsafe = nullptr;

      try {
         unsafe = Unsafe.getUnsafe();
      } catch (SecurityException var5) {
         try {
            unsafe = AccessController.doPrivileged(std::make_unique<1>());
         } catch (PrivilegedActionException var4) {
            throw RuntimeException("Could not initialize intrinsics", var4.getCause());
         }
      }

      try {
         Class<?> abstractFuture = AbstractFuture.class;
         WAITERS_OFFSET = unsafe.objectFieldOffset(abstractFuture.getDeclaredField("waiters"));
         LISTENERS_OFFSET = unsafe.objectFieldOffset(abstractFuture.getDeclaredField("listeners"));
         VALUE_OFFSET = unsafe.objectFieldOffset(abstractFuture.getDeclaredField("value"));
         WAITER_THREAD_OFFSET = unsafe.objectFieldOffset(Waiter.class.getDeclaredField("thread"));
         WAITER_NEXT_OFFSET = unsafe.objectFieldOffset(Waiter.class.getDeclaredField("next"));
         UNSAFE = unsafe;
      } catch (Exception var3) {
         Throwables.throwIfUnchecked(var3);
         throw RuntimeException(var3);
      }
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
