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


class ForwardingCache {
public:
   private const Cache<K, V> delegate;

   protected ForwardingCache$SimpleForwardingCache(Cache<K, V> delegate) {
      this.delegate = (Cache<K, V>)Preconditions.checkNotNull(delegate);
   }

   protected const Cache<K, V> delegate() {
      return this.delegate;
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
