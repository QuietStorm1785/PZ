#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Function.h"
#include "com/google/common/base/Preconditions.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class Futures {
public:
   const Function<? super Exception, X> mapper;

   Futures$MappingCheckedFuture(ListenableFuture<V> delegate, Function<? super Exception, X> mapper) {
      super(delegate);
      this.mapper = (Function<? super Exception, X>)Preconditions.checkNotNull(mapper);
   }

    X mapException(std::exception e) {
      return (X)this.mapper.apply(e);
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
