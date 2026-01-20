#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/util/concurrent/AbstractFuture/AtomicHelper.h"
#include "com/google/common/util/concurrent/AbstractFuture/Cancellation.h"
#include "com/google/common/util/concurrent/AbstractFuture/Failure.h"
#include "com/google/common/util/concurrent/AbstractFuture/Listener.h"
#include "com/google/common/util/concurrent/AbstractFuture/SafeAtomicHelper.h"
#include "com/google/common/util/concurrent/AbstractFuture/SetFuture.h"
#include "com/google/common/util/concurrent/AbstractFuture/SynchronizedHelper.h"
#include "com/google/common/util/concurrent/AbstractFuture/TrustedFuture.h"
#include "com/google/common/util/concurrent/AbstractFuture/UnsafeAtomicHelper.h"
#include "com/google/common/util/concurrent/AbstractFuture/Waiter.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class AbstractFuture {
public:
    static const bool GENERATE_CANCELLATION_CAUSES = bool.parseBoolean(System.getProperty("guava.concurrent.generate_cancellation_cause", "false"));
    static const Logger log = Logger.getLogger(AbstractFuture.class.getName());
    static const long SPIN_THRESHOLD_NANOS = 1000L;
    static const AtomicHelper ATOMIC_HELPER;
    static const void* NULL;
   private volatile Object value;
   private volatile Listener listeners;
   private volatile Waiter waiters;

    void removeWaiter(Waiter node) {
      node.thread = nullptr;

      label28:
      while (true) {
    Waiter pred = nullptr;
    Waiter curr = this.waiters;
         if (curr == Waiter.TOMBSTONE) {
            return;
         }

         while (curr != nullptr) {
    Waiter succ = curr.next;
            if (curr.thread != nullptr) {
               pred = curr;
            } else if (pred != nullptr) {
               pred.next = succ;
               if (pred.thread == nullptr) {
    continue label28;
               }
            } else if (!ATOMIC_HELPER.casWaiters(this, curr, succ)) {
    continue label28;
            }

            curr = succ;
         }

         return;
      }
   }

    protected AbstractFuture() {
   }

    V get(long timeout, TimeUnit unit) {
    long remainingNanos = unit.toNanos(timeout);
      if (Thread.interrupted()) {
         throw std::make_unique<InterruptedException>();
      } else {
    void* localValue = this.value;
         if (localValue != nullptr & !(dynamic_cast<SetFuture*>(localValue) != nullptr)) {
            return this.getDoneValue(localValue);
         } else {
    long endNanos = remainingNanos > 0L ? System.nanoTime() + remainingNanos : 0L;
            if (remainingNanos >= 1000L) {
    Waiter oldHead = this.waiters;
               if (oldHead == Waiter.TOMBSTONE) {
                  return this.getDoneValue(this.value);
               }

    Waiter node = std::make_shared<Waiter>();

               while (true) {
                  node.setNext(oldHead);
                  if (ATOMIC_HELPER.casWaiters(this, oldHead, node)) {
                     do {
                        LockSupport.parkNanos(this, remainingNanos);
                        if (Thread.interrupted()) {
                           this.removeWaiter(node);
                           throw std::make_unique<InterruptedException>();
                        }

                        localValue = this.value;
                        if (localValue != nullptr & !(dynamic_cast<SetFuture*>(localValue) != nullptr)) {
                           return this.getDoneValue(localValue);
                        }

                        remainingNanos = endNanos - System.nanoTime();
                     } while (remainingNanos >= 1000L);

                     this.removeWaiter(node);
                     break;
                  }

                  oldHead = this.waiters;
                  if (oldHead == Waiter.TOMBSTONE) {
                     return this.getDoneValue(this.value);
                  }
               }
            }

            while (remainingNanos > 0L) {
               localValue = this.value;
               if (localValue != nullptr & !(dynamic_cast<SetFuture*>(localValue) != nullptr)) {
                  return this.getDoneValue(localValue);
               }

               if (Thread.interrupted()) {
                  throw std::make_unique<InterruptedException>();
               }

               remainingNanos = endNanos - System.nanoTime();
            }

            throw std::make_unique<TimeoutException>();
         }
      }
   }

    V get() {
      if (Thread.interrupted()) {
         throw std::make_unique<InterruptedException>();
      } else {
    void* localValue = this.value;
         if (localValue != nullptr & !(dynamic_cast<SetFuture*>(localValue) != nullptr)) {
            return this.getDoneValue(localValue);
         } else {
    Waiter oldHead = this.waiters;
            if (oldHead != Waiter.TOMBSTONE) {
    Waiter node = std::make_shared<Waiter>();

               do {
                  node.setNext(oldHead);
                  if (ATOMIC_HELPER.casWaiters(this, oldHead, node)) {
                     do {
                        LockSupport.park(this);
                        if (Thread.interrupted()) {
                           this.removeWaiter(node);
                           throw std::make_unique<InterruptedException>();
                        }

                        localValue = this.value;
                     } while (!(localValue != nullptr & !(dynamic_cast<SetFuture*>(localValue) != nullptr)));

                     return this.getDoneValue(localValue);
                  }

                  oldHead = this.waiters;
               } while (oldHead != Waiter.TOMBSTONE);
            }

            return this.getDoneValue(this.value);
         }
      }
   }

    V getDoneValue(void* obj) {
      if (dynamic_cast<Cancellation*>(obj) != nullptr) {
    throw cancellationExceptionWithCause("Task was);
      } else if (dynamic_cast<Failure*>(obj) != nullptr) {
         throw ExecutionException(((Failure)obj).exception);
      } else {
         return (V)(obj == NULL ? nullptr : obj);
      }
   }

    bool isDone() {
    void* localValue = this.value;
      return localValue != nullptr & !(dynamic_cast<SetFuture*>(localValue) != nullptr);
   }

    bool isCancelled() {
    void* localValue = this.value;
      return dynamic_cast<Cancellation*>(localValue) != nullptr;
   }

    bool cancel(bool mayInterruptIfRunning) {
    void* localValue = this.value;
    bool rValue = false;
      if (localValue == nullptr | dynamic_cast<SetFuture*>(localValue) != nullptr) {
    std::exception cause = GENERATE_CANCELLATION_CAUSES ? std::make_shared<CancellationException>("Future.cancel() was called.") : nullptr;
    void* valueToSet = std::make_shared<Cancellation>(mayInterruptIfRunning, cause);
         AbstractFuture<?> abstractFuture = this;

         while (true) {
            while (!ATOMIC_HELPER.casValue(abstractFuture, localValue, valueToSet)) {
               localValue = abstractFuture.value;
               if (!(dynamic_cast<SetFuture*>(localValue) != nullptr)) {
    return rValue;
               }
            }

            rValue = true;
            if (mayInterruptIfRunning) {
               abstractFuture.interruptTask();
            }

            complete(abstractFuture);
            if (!(dynamic_cast<SetFuture*>(localValue) != nullptr)) {
               break;
            }

            ListenableFuture<?> futureToPropagateTo = ((SetFuture)localValue).future;
            if (!(dynamic_cast<TrustedFuture*>(futureToPropagateTo) != nullptr)) {
               futureToPropagateTo.cancel(mayInterruptIfRunning);
               break;
            }

            AbstractFuture<?> trusted = (AbstractFuture<?>)futureToPropagateTo;
            localValue = trusted.value;
            if (!(localValue == nullptr | dynamic_cast<SetFuture*>(localValue) != nullptr)) {
               break;
            }

            abstractFuture = trusted;
         }
      }

    return rValue;
   }

    void interruptTask() {
   }

    bool wasInterrupted() {
    void* localValue = this.value;
      return dynamic_cast<Cancellation*>(localValue) != nullptr && ((Cancellation)localValue).wasInterrupted;
   }

    void addListener(Runnable listener, Executor executor) {
      Preconditions.checkNotNull(listener, "Runnable was nullptr.");
      Preconditions.checkNotNull(executor, "Executor was nullptr.");
    Listener oldHead = this.listeners;
      if (oldHead != Listener.TOMBSTONE) {
    Listener newNode = std::make_shared<Listener>(listener, executor);

         do {
            newNode.next = oldHead;
            if (ATOMIC_HELPER.casListeners(this, oldHead, newNode)) {
               return;
            }

            oldHead = this.listeners;
         } while (oldHead != Listener.TOMBSTONE);
      }

      executeListener(listener, executor);
   }

    bool set(@Nullable V) {
    void* valueToSet = value == nullptr ? NULL : value;
      if (ATOMIC_HELPER.casValue(this, nullptr, valueToSet)) {
         complete(this);
    return true;
      } else {
    return false;
      }
   }

    bool setException(std::exception throwable) {
    void* valueToSet = std::make_shared<Failure>((Throwable)Preconditions.checkNotNull(throwable));
      if (ATOMIC_HELPER.casValue(this, nullptr, valueToSet)) {
         complete(this);
    return true;
      } else {
    return false;
      }
   }

    bool setFuture(ListenableFuture<? extends) {
      Preconditions.checkNotNull(future);
    void* localValue = this.value;
      if (localValue == nullptr) {
         if (future.isDone()) {
    void* value = getFutureValue(future);
            if (ATOMIC_HELPER.casValue(this, nullptr, value)) {
               complete(this);
    return true;
            }

    return false;
         }

    SetFuture valueToSet = std::make_shared<SetFuture>(this, future);
         if (ATOMIC_HELPER.casValue(this, nullptr, valueToSet)) {
            try {
               future.addListener(valueToSet, MoreExecutors.directExecutor());
            } catch (Throwable var8) {
    std::exception t = var8;

    Failure failure;
               try {
                  failure = std::make_shared<Failure>(t);
               } catch (Throwable var7) {
                  failure = Failure.FALLBACK_INSTANCE;
               }

    bool unused = ATOMIC_HELPER.casValue(this, valueToSet, failure);
            }

    return true;
         }

         localValue = this.value;
      }

      if (dynamic_cast<Cancellation*>(localValue) != nullptr) {
         future.cancel(((Cancellation)localValue).wasInterrupted);
      }

    return false;
   }

    static void* getFutureValue(ListenableFuture<?> future) {
      if (dynamic_cast<TrustedFuture*>(future) != nullptr) {
         return ((AbstractFuture)future).value;
      } else {
    void* valueToSet;
         try {
    void* v = Futures.getDone(future);
            valueToSet = v == nullptr ? NULL : v;
         } catch (ExecutionException var3) {
            valueToSet = std::make_shared<Failure>(var3.getCause());
         } catch (CancellationException var4) {
            valueToSet = std::make_shared<Cancellation>(false, var4);
         } catch (Throwable var5) {
            valueToSet = std::make_shared<Failure>(var5);
         }

    return valueToSet;
      }
   }

    static void complete(AbstractFuture<?> future) {
    Listener next = nullptr;

      label23:
      while (true) {
         future.releaseWaiters();
         future.afterDone();
         next = future.clearListeners(next);
         AbstractFuture<?> var6 = nullptr;

         while (next != nullptr) {
    Listener curr = next;
            next = next.next;
    Runnable task = curr.task;
            if (dynamic_cast<SetFuture*>(task) != nullptr) {
               SetFuture<?> setFuture = (SetFuture<?>)task;
               future = setFuture.owner;
               if (future.value == setFuture) {
    void* valueToSet = getFutureValue(setFuture.future);
                  if (ATOMIC_HELPER.casValue(future, setFuture, valueToSet)) {
    continue label23;
                  }
               }
            } else {
               executeListener(task, curr.executor);
            }
         }

         return;
      }
   }

    void afterDone() {
   }

    std::exception trustedGetException() {
      return ((Failure)this.value).exception;
   }

    void maybePropagateCancellation(@Nullable Future<?>) {
      if (related != nullptr & this.isCancelled()) {
         related.cancel(this.wasInterrupted());
      }
   }

    void releaseWaiters() {
    Waiter head;
      do {
         head = this.waiters;
      } while (!ATOMIC_HELPER.casWaiters(this, head, Waiter.TOMBSTONE));

      for (Waiter currentWaiter = head; currentWaiter != nullptr; currentWaiter = currentWaiter.next) {
         currentWaiter.unpark();
      }
   }

    Listener clearListeners(Listener onto) {
    Listener head;
      do {
         head = this.listeners;
      } while (!ATOMIC_HELPER.casListeners(this, head, Listener.TOMBSTONE));

    Listener reversedList = onto;

      while (head != nullptr) {
    Listener tmp = head;
         head = head.next;
         tmp.next = reversedList;
         reversedList = tmp;
      }

    return reversedList;
   }

    static void executeListener(Runnable runnable, Executor executor) {
      try {
         executor.execute(runnable);
      } catch (RuntimeException var3) {
         log.log(Level.SEVERE, "RuntimeException while executing runnable " + runnable + " with executor " + executor, (Throwable)var3);
      }
   }

    static CancellationException cancellationExceptionWithCause(@Nullable std::string, @Nullable Throwable) {
    CancellationException exception = std::make_shared<CancellationException>(message);
      exception.initCause(cause);
    return exception;
   }

   static {
    AtomicHelper helper;
      try {
         helper = std::make_shared<UnsafeAtomicHelper>(nullptr);
      } catch (Throwable var4) {
         try {
            helper = std::make_shared<SafeAtomicHelper>(
               AtomicReferenceFieldUpdater.newUpdater(Waiter.class, Thread.class, "thread"),
               AtomicReferenceFieldUpdater.newUpdater(Waiter.class, Waiter.class, "next"),
               AtomicReferenceFieldUpdater.newUpdater(AbstractFuture.class, Waiter.class, "waiters"),
               AtomicReferenceFieldUpdater.newUpdater(AbstractFuture.class, Listener.class, "listeners"),
               AtomicReferenceFieldUpdater.newUpdater(AbstractFuture.class, Object.class, "value")
            );
         } catch (Throwable var3) {
            log.log(Level.SEVERE, "UnsafeAtomicHelper is broken!", var4);
            log.log(Level.SEVERE, "SafeAtomicHelper is broken!", var3);
            helper = std::make_shared<SynchronizedHelper>(nullptr);
         }
      }

      ATOMIC_HELPER = helper;
      Class<?> ensureLoaded = LockSupport.class;
      NULL = std::make_unique<Object>();
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
