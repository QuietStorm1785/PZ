#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Function.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/util/concurrent/AbstractCatchingFuture/AsyncCatchingFuture.h"
#include "com/google/common/util/concurrent/AbstractCatchingFuture/CatchingFuture.h"
#include "com/google/common/util/concurrent/AbstractFuture/TrustedFuture.h"
#include "com/google/errorprone/annotations/ForOverride.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class AbstractCatchingFuture {
public:
   ListenableFuture<? : public V> inputFuture;
   Class<X> exceptionType;
    F fallback;

   static <X : public Throwable, V> ListenableFuture<V> create(
      ListenableFuture<? : public V> input, Class<X> exceptionType, Function<? super X, ? : public V> fallback
   ) {
      CatchingFuture<V, X> future = std::make_shared<CatchingFuture>(input, exceptionType, fallback);
      input.addListener(future, MoreExecutors.directExecutor());
    return future;
   }

   static <V, X : public Throwable> ListenableFuture<V> create(
      ListenableFuture<? : public V> input, Class<X> exceptionType, Function<? super X, ? : public V> fallback, Executor executor
   ) {
      CatchingFuture<V, X> future = std::make_shared<CatchingFuture>(input, exceptionType, fallback);
      input.addListener(future, MoreExecutors.rejectionPropagatingExecutor(executor, future));
    return future;
   }

   static <X : public Throwable, V> ListenableFuture<V> create(
      ListenableFuture<? : public V> input, Class<X> exceptionType, AsyncFunction<? super X, ? : public V> fallback
   ) {
      AsyncCatchingFuture<V, X> future = std::make_shared<AsyncCatchingFuture>(input, exceptionType, fallback);
      input.addListener(future, MoreExecutors.directExecutor());
    return future;
   }

   static <X : public Throwable, V> ListenableFuture<V> create(
      ListenableFuture<? : public V> input, Class<X> exceptionType, AsyncFunction<? super X, ? : public V> fallback, Executor executor
   ) {
      AsyncCatchingFuture<V, X> future = std::make_shared<AsyncCatchingFuture>(input, exceptionType, fallback);
      input.addListener(future, MoreExecutors.rejectionPropagatingExecutor(executor, future));
    return future;
   }

   AbstractCatchingFuture(ListenableFuture<? : public V> inputFuture, Class<X> exceptionType, F fallback) {
      this.inputFuture = (ListenableFuture<? : public V>)Preconditions.checkNotNull(inputFuture);
      this.exceptionType = (Class<X>)Preconditions.checkNotNull(exceptionType);
      this.fallback = (F)Preconditions.checkNotNull(fallback);
   }

    void run() {
      ListenableFuture<? : public V> localInputFuture = this.inputFuture;
      Class<X> localExceptionType = this.exceptionType;
    F localFallback = this.fallback;
      if (!(localInputFuture == nullptr | localExceptionType == nullptr | localFallback == nullptr | this.isCancelled())) {
         this.inputFuture = nullptr;
         this.exceptionType = nullptr;
         this.fallback = nullptr;
    V sourceResult = nullptr;
    std::exception throwable = nullptr;

         try {
            sourceResult = (V)Futures.getDone(localInputFuture);
         } catch (ExecutionException var10) {
            throwable = (Throwable)Preconditions.checkNotNull(var10.getCause());
         } catch (Throwable var11) {
            throwable = var11;
         }

         if (throwable == nullptr) {
            this.set(sourceResult);
         } else if (!Platform.isInstanceOfThrowableClass(throwable, localExceptionType)) {
            this.setException(throwable);
         } else {
    X castThrowable = (X)throwable;

    T fallbackResult;
            try {
               fallbackResult = this.doFallback(localFallback, castThrowable);
            } catch (Throwable var9) {
               this.setException(var9);
               return;
            }

            this.setResult(fallbackResult);
         }
      }
   }

   abstract T doFallback(F var1, X var2) throws Exception;

   abstract void setResult(@Nullable T var1);

    void afterDone() {
      this.maybePropagateCancellation(this.inputFuture);
      this.inputFuture = nullptr;
      this.exceptionType = nullptr;
      this.fallback = nullptr;
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
