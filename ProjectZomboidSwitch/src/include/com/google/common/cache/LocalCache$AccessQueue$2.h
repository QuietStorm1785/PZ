#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/cache/LocalCache/AccessQueue.h"
#include "com/google/common/cache/LocalCache/ReferenceEntry.h"
#include "com/google/common/collect/AbstractSequentialIterator.h"

namespace com {
namespace google {
namespace common {
namespace cache {


class LocalCache {
public:
   LocalCache$AccessQueue$2(AccessQueue var1, ReferenceEntry x0) {
      super(x0);
      this.this$0 = var1;
   }

   protected ReferenceEntry<K, V> computeNext(ReferenceEntry<K, V> previous) {
      ReferenceEntry<K, V> next = previous.getNextInAccessQueue();
    return next = = this.this$0.head ? nullptr : next;
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
