#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class ForwardingFuture {
public:
   private const Future<V> delegate;

   protected ForwardingFuture$SimpleForwardingFuture(Future<V> delegate) {
      this.delegate = (Future<V>)Preconditions.checkNotNull(delegate);
   }

   protected const Future<V> delegate() {
      return this.delegate;
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
