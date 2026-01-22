#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/cache/RemovalListeners/1.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace cache {


class RemovalListeners {
public:
    private RemovalListeners() {
   }

   public static <K, V> RemovalListener<K, V> asynchronous(RemovalListener<K, V> listener, Executor executor) {
      Preconditions.checkNotNull(listener);
      Preconditions.checkNotNull(executor);
      return std::make_shared<1>(executor, listener);
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
