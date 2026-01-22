#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Function.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class AbstractTransformFuture {
public:
   AbstractTransformFuture$TransformFuture(ListenableFuture<? : public I> inputFuture, Function<? super I, ? : public O> function) {
      super(inputFuture, function);
   }

    O doTransform(Function<? super, ? extends, @Nullable I) {
      return (O)function.apply(input);
   }

    void setResult(@Nullable O) {
      this.set(result);
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
