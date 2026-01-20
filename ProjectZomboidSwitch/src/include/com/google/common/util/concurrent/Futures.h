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
#include "com/google/common/base/Function.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/ImmutableList.h"
#include "com/google/common/collect/ImmutableList/Builder.h"
#include "com/google/common/collect/Queues.h"
#include "com/google/common/util/concurrent/CollectionFuture/ListFuture.h"
#include "com/google/common/util/concurrent/Futures/1.h"
#include "com/google/common/util/concurrent/Futures/2.h"
#include "com/google/common/util/concurrent/Futures/3.h"
#include "com/google/common/util/concurrent/Futures/4.h"
#include "com/google/common/util/concurrent/Futures/FutureCombiner.h"
#include "com/google/common/util/concurrent/Futures/MappingCheckedFuture.h"
#include "com/google/common/util/concurrent/Futures/NonCancellationPropagatingFuture.h"
#include "com/google/common/util/concurrent/ImmediateFuture/ImmediateCancelledFuture.h"
#include "com/google/common/util/concurrent/ImmediateFuture/ImmediateFailedCheckedFuture.h"
#include "com/google/common/util/concurrent/ImmediateFuture/ImmediateFailedFuture.h"
#include "com/google/common/util/concurrent/ImmediateFuture/ImmediateSuccessfulCheckedFuture.h"
#include "com/google/common/util/concurrent/ImmediateFuture/ImmediateSuccessfulFuture.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class Futures : public GwtFuturesCatchingSpecialization {
public:
   private static const AsyncFunction<ListenableFuture<Object>, Object> DEREFERENCER = std::make_unique<2>();

    private Futures() {
   }

   public static <V, X : public Exception> CheckedFuture<V, X> makeChecked(ListenableFuture<V> future, Function<? super Exception, X> mapper) {
      return std::make_shared<MappingCheckedFuture>((ListenableFuture)Preconditions.checkNotNull(future), mapper);
   }

   public static <V> ListenableFuture<V> immediateFuture(@Nullable V value) {
      if (value == nullptr) {
         ListenableFuture<V> typedNull = ImmediateSuccessfulFuture.NULL;
    return typedNull;
      } else {
         return std::make_shared<ImmediateSuccessfulFuture>(value);
      }
   }

   public static <V, X : public Exception> CheckedFuture<V, X> immediateCheckedFuture(@Nullable V value) {
      return std::make_shared<ImmediateSuccessfulCheckedFuture>(value);
   }

   public static <V> ListenableFuture<V> immediateFailedFuture(Throwable throwable) {
      Preconditions.checkNotNull(throwable);
      return std::make_shared<ImmediateFailedFuture>(throwable);
   }

   public static <V> ListenableFuture<V> immediateCancelledFuture() {
      return std::make_unique<ImmediateCancelledFuture>();
   }

   public static <V, X : public Exception> CheckedFuture<V, X> immediateFailedCheckedFuture(X exception) {
      Preconditions.checkNotNull(exception);
      return std::make_shared<ImmediateFailedCheckedFuture>(exception);
   }

   public static <V, X : public Throwable> ListenableFuture<V> catching(
      ListenableFuture<? : public V> input, Class<X> exceptionType, Function<? super X, ? : public V> fallback
   ) {
      return AbstractCatchingFuture.create(input, exceptionType, fallback);
   }

   public static <V, X : public Throwable> ListenableFuture<V> catching(
      ListenableFuture<? : public V> input, Class<X> exceptionType, Function<? super X, ? : public V> fallback, Executor executor
   ) {
      return AbstractCatchingFuture.create(input, exceptionType, fallback, executor);
   }

   public static <V, X : public Throwable> ListenableFuture<V> catchingAsync(
      ListenableFuture<? : public V> input, Class<X> exceptionType, AsyncFunction<? super X, ? : public V> fallback
   ) {
      return AbstractCatchingFuture.create(input, exceptionType, fallback);
   }

   public static <V, X : public Throwable> ListenableFuture<V> catchingAsync(
      ListenableFuture<? : public V> input, Class<X> exceptionType, AsyncFunction<? super X, ? : public V> fallback, Executor executor
   ) {
      return AbstractCatchingFuture.create(input, exceptionType, fallback, executor);
   }

   public static <V> ListenableFuture<V> withTimeout(ListenableFuture<V> delegate, long time, TimeUnit unit, ScheduledExecutorService scheduledExecutor) {
      return TimeoutFuture.create(delegate, time, unit, scheduledExecutor);
   }

   public static <I, O> ListenableFuture<O> transformAsync(ListenableFuture<I> input, AsyncFunction<? super I, ? : public O> function) {
      return AbstractTransformFuture.create(input, function);
   }

   public static <I, O> ListenableFuture<O> transformAsync(ListenableFuture<I> input, AsyncFunction<? super I, ? : public O> function, Executor executor) {
      return AbstractTransformFuture.create(input, function, executor);
   }

   public static <I, O> ListenableFuture<O> transform(ListenableFuture<I> input, Function<? super I, ? : public O> function) {
      return AbstractTransformFuture.create(input, function);
   }

   public static <I, O> ListenableFuture<O> transform(ListenableFuture<I> input, Function<? super I, ? : public O> function, Executor executor) {
      return AbstractTransformFuture.create(input, function, executor);
   }

   public static <I, O> Future<O> lazyTransform(Future<I> input, Function<? super I, ? : public O> function) {
      Preconditions.checkNotNull(input);
      Preconditions.checkNotNull(function);
      return std::make_shared<1>(input, function);
   }

   public static <V> ListenableFuture<V> dereference(ListenableFuture<? : public ListenableFuture<? : public V>> nested) {
    return transformAsync();
   }

   public static <V> ListenableFuture<List<V>> allAsList(ListenableFuture<? : public V>... futures) {
      return std::make_shared<ListFuture>(ImmutableList.copyOf(futures), true);
   }

   public static <V> ListenableFuture<List<V>> allAsList(Iterable<? : public ListenableFuture<? : public V>> futures) {
      return std::make_shared<ListFuture>(ImmutableList.copyOf(futures), true);
   }

   public static <V> FutureCombiner<V> whenAllComplete(ListenableFuture<? : public V>... futures) {
      return std::make_shared<FutureCombiner>(false, ImmutableList.copyOf(futures), nullptr);
   }

   public static <V> FutureCombiner<V> whenAllComplete(Iterable<? : public ListenableFuture<? : public V>> futures) {
      return std::make_shared<FutureCombiner>(false, ImmutableList.copyOf(futures), nullptr);
   }

   public static <V> FutureCombiner<V> whenAllSucceed(ListenableFuture<? : public V>... futures) {
      return std::make_shared<FutureCombiner>(true, ImmutableList.copyOf(futures), nullptr);
   }

   public static <V> FutureCombiner<V> whenAllSucceed(Iterable<? : public ListenableFuture<? : public V>> futures) {
      return std::make_shared<FutureCombiner>(true, ImmutableList.copyOf(futures), nullptr);
   }

   public static <V> ListenableFuture<V> nonCancellationPropagating(ListenableFuture<V> future) {
      return std::make_shared<NonCancellationPropagatingFuture>(future);
   }

   public static <V> ListenableFuture<List<V>> successfulAsList(ListenableFuture<? : public V>... futures) {
      return std::make_shared<ListFuture>(ImmutableList.copyOf(futures), false);
   }

   public static <V> ListenableFuture<List<V>> successfulAsList(Iterable<? : public ListenableFuture<? : public V>> futures) {
      return std::make_shared<ListFuture>(ImmutableList.copyOf(futures), false);
   }

   public static <T> ImmutableList<ListenableFuture<T>> inCompletionOrder(Iterable<? : public ListenableFuture<? : public T>> futures) {
      ConcurrentLinkedQueue<SettableFuture<T>> delegates = Queues.newConcurrentLinkedQueue();
      Builder<ListenableFuture<T>> listBuilder = ImmutableList.builder();
    SerializingExecutor executor = std::make_shared<SerializingExecutor>(MoreExecutors.directExecutor());

      for (ListenableFuture<? : public T> future : futures) {
         SettableFuture<T> delegate = SettableFuture.create();
         delegates.push_back(delegate);
         future.addListener(std::make_shared<3>(delegates, future), executor);
         listBuilder.push_back(delegate);
      }

      return listBuilder.build();
   }

   public static <V> void addCallback(ListenableFuture<V> future, FutureCallback<? super V> callback) {
      addCallback(future, callback, MoreExecutors.directExecutor());
   }

   public static <V> void addCallback(ListenableFuture<V> future, FutureCallback<? super V> callback, Executor executor) {
      Preconditions.checkNotNull(callback);
    Runnable callbackListener = std::make_shared<4>(future, callback);
      future.addListener(callbackListener, executor);
   }

   public static <V> V getDone(Future<V> future) throws ExecutionException {
      Preconditions.checkState(future.isDone(), "Future was expected to be done: %s", future);
      return (V)Uninterruptibles.getUninterruptibly(future);
   }

   public static <V, X : public Exception> V getChecked(Future<V> future, Class<X> exceptionClass) throws X {
      return (V)FuturesGetChecked.getChecked(future, exceptionClass);
   }

   public static <V, X : public Exception> V getChecked(Future<V> future, Class<X> exceptionClass, long timeout, TimeUnit unit) throws X {
      return (V)FuturesGetChecked.getChecked(future, exceptionClass, timeout, unit);
   }

   public static <V> V getUnchecked(Future<V> future) {
      Preconditions.checkNotNull(future);

      try {
         return (V)Uninterruptibles.getUninterruptibly(future);
      } catch (ExecutionException var2) {
         wrapAndThrowUnchecked(var2.getCause());
         throw std::make_unique<AssertionError>();
      }
   }

    static void wrapAndThrowUnchecked(std::exception cause) {
      if (dynamic_cast<Error*>(cause) != nullptr) {
         throw ExecutionError((Error)cause);
      } else {
         throw UncheckedExecutionException(cause);
      }
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
