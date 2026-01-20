#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class AbstractTransformFuture {
public:
   : public AbstractTransformFuture<I, O, AsyncFunction<? super I, ? : public O>, ListenableFuture<? : public O>> {
   AbstractTransformFuture$AsyncTransformFuture(ListenableFuture<? : public I> inputFuture, AsyncFunction<? super I, ? : public O> function) {
      super(inputFuture, function);
   }

   ListenableFuture<? : public O> doTransform(AsyncFunction<? super I, ? : public O> function, @Nullable I input) throws Exception {
      ListenableFuture<? : public O> outputFuture = function.apply(input);
      Preconditions.checkNotNull(outputFuture, "AsyncFunction.apply returned nullptr instead of a Future. Did you mean to return immediateFuture(nullptr)?");
    return outputFuture;
   }

    void setResult(ListenableFuture<? extends) {
      this.setFuture(result);
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
