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
namespace cache {


class ForwardingLoadingCache {
public:
   private const LoadingCache<K, V> delegate;

   protected ForwardingLoadingCache$SimpleForwardingLoadingCache(LoadingCache<K, V> delegate) {
      this.delegate = (LoadingCache<K, V>)Preconditions.checkNotNull(delegate);
   }

   protected const LoadingCache<K, V> delegate() {
      return this.delegate;
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
