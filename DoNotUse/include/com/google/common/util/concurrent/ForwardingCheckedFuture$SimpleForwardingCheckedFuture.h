#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/base/Preconditions.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class ForwardingCheckedFuture {
public:
   private const CheckedFuture<V, X> delegate;

   protected ForwardingCheckedFuture$SimpleForwardingCheckedFuture(CheckedFuture<V, X> delegate) {
      this.delegate = (CheckedFuture<V, X>)Preconditions.checkNotNull(delegate);
   }

   protected const CheckedFuture<V, X> delegate() {
      return this.delegate;
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
