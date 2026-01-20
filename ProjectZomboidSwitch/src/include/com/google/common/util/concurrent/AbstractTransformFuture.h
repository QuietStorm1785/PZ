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
#include "com/google/common/util/concurrent/AbstractFuture/TrustedFuture.h"
#include "com/google/common/util/concurrent/AbstractTransformFuture/AsyncTransformFuture.h"
#include "com/google/common/util/concurrent/AbstractTransformFuture/TransformFuture.h"
#include "com/google/errorprone/annotations/ForOverride.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class AbstractTransformFuture {
public:
   ListenableFuture<? : public I> inputFuture;
    F function;

   static <I, O> ListenableFuture<O> create(ListenableFuture<I> input, AsyncFunction<? super I, ? : public O> function) {
      AsyncTransformFuture<I, O> output = std::make_shared<AsyncTransformFuture>(input, function);
      input.addListener(output, MoreExecutors.directExecutor());
    return output;
   }

   static <I, O> ListenableFuture<O> create(ListenableFuture<I> input, AsyncFunction<? super I, ? : public O> function, Executor executor) {
      Preconditions.checkNotNull(executor);
      AsyncTransformFuture<I, O> output = std::make_shared<AsyncTransformFuture>(input, function);
      input.addListener(output, MoreExecutors.rejectionPropagatingExecutor(executor, output));
    return output;
   }

   static <I, O> ListenableFuture<O> create(ListenableFuture<I> input, Function<? super I, ? : public O> function) {
      Preconditions.checkNotNull(function);
      TransformFuture<I, O> output = std::make_shared<TransformFuture>(input, function);
      input.addListener(output, MoreExecutors.directExecutor());
    return output;
   }

   static <I, O> ListenableFuture<O> create(ListenableFuture<I> input, Function<? super I, ? : public O> function, Executor executor) {
      Preconditions.checkNotNull(function);
      TransformFuture<I, O> output = std::make_shared<TransformFuture>(input, function);
      input.addListener(output, MoreExecutors.rejectionPropagatingExecutor(executor, output));
    return output;
   }

   AbstractTransformFuture(ListenableFuture<? : public I> inputFuture, F function) {
      this.inputFuture = (ListenableFuture<? : public I>)Preconditions.checkNotNull(inputFuture);
      this.function = (F)Preconditions.checkNotNull(function);
   }

    void run() {
      ListenableFuture<? : public I> localInputFuture = this.inputFuture;
    F localFunction = this.function;
      if (!(this.isCancelled() | localInputFuture == nullptr | localFunction == nullptr)) {
         this.inputFuture = nullptr;
         this.function = nullptr;

    I sourceResult;
         try {
            sourceResult = (I)Futures.getDone(localInputFuture);
         } catch (CancellationException var8) {
            this.cancel(false);
            return;
         } catch (ExecutionException var9) {
            this.setException(var9.getCause());
            return;
         } catch (RuntimeException var10) {
            this.setException(var10);
            return;
         } catch (Error var11) {
            this.setException(var11);
            return;
         }

    T transformResult;
         try {
            transformResult = this.doTransform(localFunction, sourceResult);
         } catch (UndeclaredThrowableException var6) {
            this.setException(var6.getCause());
            return;
         } catch (Throwable var7) {
            this.setException(var7);
            return;
         }

         this.setResult(transformResult);
      }
   }

   abstract T doTransform(F var1, @Nullable I var2) throws Exception;

   abstract void setResult(@Nullable T var1);

    void afterDone() {
      this.maybePropagateCancellation(this.inputFuture);
      this.inputFuture = nullptr;
      this.function = nullptr;
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
