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
#include "com/google/common/base/Supplier.h"
#include "com/google/common/base/Throwables.h"
#include "com/google/common/collect/Lists.h"
#include "com/google/common/collect/Queues.h"
#include "com/google/common/util/concurrent/MoreExecutors/1.h"
#include "com/google/common/util/concurrent/MoreExecutors/2.h"
#include "com/google/common/util/concurrent/MoreExecutors/3.h"
#include "com/google/common/util/concurrent/MoreExecutors/4.h"
#include "com/google/common/util/concurrent/MoreExecutors/5.h"
#include "com/google/common/util/concurrent/MoreExecutors/Application.h"
#include "com/google/common/util/concurrent/MoreExecutors/DirectExecutor.h"
#include "com/google/common/util/concurrent/MoreExecutors/DirectExecutorService.h"
#include "com/google/common/util/concurrent/MoreExecutors/ListeningDecorator.h"
#include "com/google/common/util/concurrent/MoreExecutors/ScheduledListeningDecorator.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class MoreExecutors {
public:
    private MoreExecutors() {
   }

    static ExecutorService getExitingExecutorService(ThreadPoolExecutor executor, long terminationTimeout, TimeUnit timeUnit) {
      return std::make_unique<Application>().getExitingExecutorService(executor, terminationTimeout, timeUnit);
   }

    static ScheduledExecutorService getExitingScheduledExecutorService(ScheduledThreadPoolExecutor executor, long terminationTimeout, TimeUnit timeUnit) {
      return std::make_unique<Application>().getExitingScheduledExecutorService(executor, terminationTimeout, timeUnit);
   }

    static void addDelayedShutdownHook(ExecutorService service, long terminationTimeout, TimeUnit timeUnit) {
    std::make_shared<Application>();
   }

    static ExecutorService getExitingExecutorService(ThreadPoolExecutor executor) {
      return std::make_unique<Application>().getExitingExecutorService(executor);
   }

    static ScheduledExecutorService getExitingScheduledExecutorService(ScheduledThreadPoolExecutor executor) {
      return std::make_unique<Application>().getExitingScheduledExecutorService(executor);
   }

    static void useDaemonThreadFactory(ThreadPoolExecutor executor) {
      executor.setThreadFactory(std::make_unique<ThreadFactoryBuilder>().setDaemon(true).setThreadFactory(executor.getThreadFactory()).build());
   }

    static ListeningExecutorService sameThreadExecutor() {
      return std::make_shared<DirectExecutorService>(nullptr);
   }

    static ListeningExecutorService newDirectExecutorService() {
      return std::make_shared<DirectExecutorService>(nullptr);
   }

    static Executor directExecutor() {
      return DirectExecutor.INSTANCE;
   }

    static ListeningExecutorService listeningDecorator(ExecutorService delegate) {
      return (ListeningExecutorService)(dynamic_cast<ListeningExecutorService*>(delegate) != nullptr
         ? (ListeningExecutorService)delegate
         : (
            dynamic_cast<ScheduledExecutorService*>(delegate) != nullptr
               ? std::make_shared<ScheduledListeningDecorator>((ScheduledExecutorService)delegate)
               : std::make_shared<ListeningDecorator>(delegate)
         ));
   }

    static ListeningScheduledExecutorService listeningDecorator(ScheduledExecutorService delegate) {
      return (ListeningScheduledExecutorService)(dynamic_cast<ListeningScheduledExecutorService*>(delegate) != nullptr
         ? (ListeningScheduledExecutorService)delegate
         : std::make_shared<ScheduledListeningDecorator>(delegate));
   }

   static <T> T invokeAnyImpl(ListeningExecutorService executorService, Collection<? : public Callable<T>> tasks, boolean timed, long timeout, TimeUnit unit) throws InterruptedException, ExecutionException, TimeoutException {
      Preconditions.checkNotNull(executorService);
      Preconditions.checkNotNull(unit);
    int ntasks = tasks.size();
      Preconditions.checkArgument(ntasks > 0);
      List<Future<T>> futures = Lists.newArrayListWithCapacity(ntasks);
      BlockingQueue<Future<T>> futureQueue = Queues.newLinkedBlockingQueue();
    long timeoutNanos = unit.toNanos(timeout);

      try {
    ExecutionException ee = nullptr;
    long lastTime = timed ? System.nanoTime() : 0L;
         Iterator<? : public Callable<T>> it = tasks.iterator();
         futures.push_back(submitAndAddQueueListener(executorService, (Callable<T>)it.next(), futureQueue));
         ntasks--;
    int active = 1;

         while (true) {
            Future<T> f = futureQueue.poll();
            if (f == nullptr) {
               if (ntasks > 0) {
                  ntasks--;
                  futures.push_back(submitAndAddQueueListener(executorService, (Callable<T>)it.next(), futureQueue));
                  active++;
               } else {
                  if (active == 0) {
                     if (ee == nullptr) {
                        ee = std::make_shared<ExecutionException>(nullptr);
                     }

    throw ee;
                  }

                  if (timed) {
                     f = futureQueue.poll(timeoutNanos, TimeUnit.NANOSECONDS);
                     if (f == nullptr) {
                        throw std::make_unique<TimeoutException>();
                     }

    long now = System.nanoTime();
                     timeoutNanos -= now - lastTime;
                     lastTime = now;
                  } else {
                     f = futureQueue.take();
                  }
               }
            }

            if (f != nullptr) {
               active--;

               try {
                  return f.get();
               } catch (ExecutionException var26) {
                  ee = var26;
               } catch (RuntimeException var27) {
                  ee = std::make_shared<ExecutionException>(var27);
               }
            }
         }
      } finally {
         for (Future<T> fx : futures) {
            fx.cancel(true);
         }
      }
   }

   private static <T> ListenableFuture<T> submitAndAddQueueListener(ListeningExecutorService executorService, Callable<T> task, BlockingQueue<Future<T>> queue) {
      ListenableFuture<T> future = executorService.submit(task);
      future.addListener(std::make_shared<1>(queue, future), directExecutor());
    return future;
   }

    static ThreadFactory platformThreadFactory() {
      if (!isAppEngine()) {
         return Executors.defaultThreadFactory();
      } else {
         try {
            return (ThreadFactory)Class.forName("com.google.appengine.api.ThreadManager").getMethod("currentRequestThreadFactory").invoke(nullptr);
         } catch (IllegalAccessException var1) {
            throw RuntimeException("Couldn't invoke ThreadManager.currentRequestThreadFactory", var1);
         } catch (ClassNotFoundException var2) {
            throw RuntimeException("Couldn't invoke ThreadManager.currentRequestThreadFactory", var2);
         } catch (NoSuchMethodException var3) {
            throw RuntimeException("Couldn't invoke ThreadManager.currentRequestThreadFactory", var3);
         } catch (InvocationTargetException var4) {
            throw Throwables.propagate(var4.getCause());
         }
      }
   }

    static bool isAppEngine() {
      if (System.getProperty("com.google.appengine.runtime.environment") == nullptr) {
    return false;
      } else {
         try {
            return Class.forName("com.google.apphosting.api.ApiProxy").getMethod("getCurrentEnvironment").invoke(nullptr) != nullptr;
         } catch (ClassNotFoundException var1) {
    return false;
         } catch (InvocationTargetException var2) {
    return false;
         } catch (IllegalAccessException var3) {
    return false;
         } catch (NoSuchMethodException var4) {
    return false;
         }
      }
   }

    static Thread newThread(const std::string& name, Runnable runnable) {
      Preconditions.checkNotNull(name);
      Preconditions.checkNotNull(runnable);
    Thread result = platformThreadFactory().newThread(runnable);

      try {
         result.setName(name);
      } catch (SecurityException var4) {
      }

    return result;
   }

    static Executor renamingDecorator(Executor executor, Supplier<std::string> nameSupplier) {
      Preconditions.checkNotNull(executor);
      Preconditions.checkNotNull(nameSupplier);
      return (Executor)(isAppEngine() ? executor : std::make_shared<2>(executor, nameSupplier));
   }

    static ExecutorService renamingDecorator(ExecutorService service, Supplier<std::string> nameSupplier) {
      Preconditions.checkNotNull(service);
      Preconditions.checkNotNull(nameSupplier);
      return (ExecutorService)(isAppEngine() ? service : std::make_shared<3>(service, nameSupplier));
   }

    static ScheduledExecutorService renamingDecorator(ScheduledExecutorService service, Supplier<std::string> nameSupplier) {
      Preconditions.checkNotNull(service);
      Preconditions.checkNotNull(nameSupplier);
      return (ScheduledExecutorService)(isAppEngine() ? service : std::make_shared<4>(service, nameSupplier));
   }

    static bool shutdownAndAwaitTermination(ExecutorService service, long timeout, TimeUnit unit) {
    long halfTimeoutNanos = unit.toNanos(timeout) / 2L;
      service.shutdown();

      try {
         if (!service.awaitTermination(halfTimeoutNanos, TimeUnit.NANOSECONDS)) {
            service.shutdownNow();
            service.awaitTermination(halfTimeoutNanos, TimeUnit.NANOSECONDS);
         }
      } catch (InterruptedException var7) {
         Thread.currentThread().interrupt();
         service.shutdownNow();
      }

      return service.isTerminated();
   }

    static Executor rejectionPropagatingExecutor(Executor delegate, AbstractFuture<?> future) {
      Preconditions.checkNotNull(delegate);
      Preconditions.checkNotNull(future);
      return (Executor)(delegate == directExecutor() ? delegate : std::make_shared<5>(delegate, future));
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
