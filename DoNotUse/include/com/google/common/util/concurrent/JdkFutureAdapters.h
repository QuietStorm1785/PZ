#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/util/concurrent/JdkFutureAdapters/ListenableFutureAdapter.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class JdkFutureAdapters {
public:
   public static <V> ListenableFuture<V> listenInPoolThread(Future<V> future) {
      return (ListenableFuture<V>)(dynamic_cast<ListenableFuture*>(future) != nullptr ? (ListenableFuture)future : std::make_shared<ListenableFutureAdapter>(future));
   }

   public static <V> ListenableFuture<V> listenInPoolThread(Future<V> future, Executor executor) {
      Preconditions.checkNotNull(executor);
      return (ListenableFuture<V>)(dynamic_cast<ListenableFuture*>(future) != nullptr ? (ListenableFuture)future : std::make_shared<ListenableFutureAdapter>(future, executor));
   }

    private JdkFutureAdapters() {
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
