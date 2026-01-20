#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class ForwardingListenableFuture {
public:
   private const ListenableFuture<V> delegate;

   protected ForwardingListenableFuture$SimpleForwardingListenableFuture(ListenableFuture<V> delegate) {
      this.delegate = (ListenableFuture<V>)Preconditions.checkNotNull(delegate);
   }

   protected const ListenableFuture<V> delegate() {
      return this.delegate;
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
