#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class Uninterruptibles {
public:
    static void awaitUninterruptibly(CountDownLatch latch) {
    bool interrupted = false;

      try {
         while (true) {
            try {
               latch.await();
               return;
            } catch (InterruptedException var6) {
               interrupted = true;
            }
         }
      } finally {
         if (interrupted) {
            Thread.currentThread().interrupt();
         }
      }
   }

    static bool awaitUninterruptibly(CountDownLatch latch, long timeout, TimeUnit unit) {
    bool interrupted = false;

      try {
    long remainingNanos = unit.toNanos(timeout);
    long end = System.nanoTime() + remainingNanos;

         while (true) {
            try {
               return latch.await(remainingNanos, TimeUnit.NANOSECONDS);
            } catch (InterruptedException var13) {
               interrupted = true;
               remainingNanos = end - System.nanoTime();
            }
         }
      } finally {
         if (interrupted) {
            Thread.currentThread().interrupt();
         }
      }
   }

    static void joinUninterruptibly(Thread toJoin) {
    bool interrupted = false;

      try {
         while (true) {
            try {
               toJoin.join();
               return;
            } catch (InterruptedException var6) {
               interrupted = true;
            }
         }
      } finally {
         if (interrupted) {
            Thread.currentThread().interrupt();
         }
      }
   }

   public static <V> V getUninterruptibly(Future<V> future) throws ExecutionException {
    bool interrupted = false;

      try {
         while (true) {
            try {
               return future.get();
            } catch (InterruptedException var6) {
               interrupted = true;
            }
         }
      } finally {
         if (interrupted) {
            Thread.currentThread().interrupt();
         }
      }
   }

   public static <V> V getUninterruptibly(Future<V> future, long timeout, TimeUnit unit) throws ExecutionException, TimeoutException {
    bool interrupted = false;

      try {
    long remainingNanos = unit.toNanos(timeout);
    long end = System.nanoTime() + remainingNanos;

         while (true) {
            try {
               return future.get(remainingNanos, TimeUnit.NANOSECONDS);
            } catch (InterruptedException var13) {
               interrupted = true;
               remainingNanos = end - System.nanoTime();
            }
         }
      } finally {
         if (interrupted) {
            Thread.currentThread().interrupt();
         }
      }
   }

    static void joinUninterruptibly(Thread toJoin, long timeout, TimeUnit unit) {
      Preconditions.checkNotNull(toJoin);
    bool interrupted = false;

      try {
    long remainingNanos = unit.toNanos(timeout);
    long end = System.nanoTime() + remainingNanos;

         while (true) {
            try {
               TimeUnit.NANOSECONDS.timedJoin(toJoin, remainingNanos);
               return;
            } catch (InterruptedException var13) {
               interrupted = true;
               remainingNanos = end - System.nanoTime();
            }
         }
      } finally {
         if (interrupted) {
            Thread.currentThread().interrupt();
         }
      }
   }

   public static <E> E takeUninterruptibly(BlockingQueue<E> queue) {
    bool interrupted = false;

      try {
         while (true) {
            try {
               return queue.take();
            } catch (InterruptedException var6) {
               interrupted = true;
            }
         }
      } finally {
         if (interrupted) {
            Thread.currentThread().interrupt();
         }
      }
   }

   public static <E> void putUninterruptibly(BlockingQueue<E> queue, E element) {
    bool interrupted = false;

      try {
         while (true) {
            try {
               queue.put(element);
               return;
            } catch (InterruptedException var7) {
               interrupted = true;
            }
         }
      } finally {
         if (interrupted) {
            Thread.currentThread().interrupt();
         }
      }
   }

    static void sleepUninterruptibly(long sleepFor, TimeUnit unit) {
    bool interrupted = false;

      try {
    long remainingNanos = unit.toNanos(sleepFor);
    long end = System.nanoTime() + remainingNanos;

         while (true) {
            try {
               TimeUnit.NANOSECONDS.sleep(remainingNanos);
               return;
            } catch (InterruptedException var12) {
               interrupted = true;
               remainingNanos = end - System.nanoTime();
            }
         }
      } finally {
         if (interrupted) {
            Thread.currentThread().interrupt();
         }
      }
   }

    static bool tryAcquireUninterruptibly(Semaphore semaphore, long timeout, TimeUnit unit) {
    return tryAcquireUninterruptibly();
   }

    static bool tryAcquireUninterruptibly(Semaphore semaphore, int permits, long timeout, TimeUnit unit) {
    bool interrupted = false;

      try {
    long remainingNanos = unit.toNanos(timeout);
    long end = System.nanoTime() + remainingNanos;

         while (true) {
            try {
               return semaphore.tryAcquire(permits, remainingNanos, TimeUnit.NANOSECONDS);
            } catch (InterruptedException var14) {
               interrupted = true;
               remainingNanos = end - System.nanoTime();
            }
         }
      } finally {
         if (interrupted) {
            Thread.currentThread().interrupt();
         }
      }
   }

    private Uninterruptibles() {
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
