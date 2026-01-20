#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/cache/LocalCache/AbstractReferenceEntry.h"
#include "com/google/common/cache/LocalCache/AccessQueue.h"
#include "com/google/common/cache/LocalCache/ReferenceEntry.h"

namespace com {
namespace google {
namespace common {
namespace cache {


class LocalCache {
public:
   ReferenceEntry<K, V> nextAccess;
   ReferenceEntry<K, V> previousAccess;

   LocalCache$AccessQueue$1(AccessQueue var1) {
      this.this$0 = var1;
      this.nextAccess = this;
      this.previousAccess = this;
   }

    long getAccessTime() {
      return int64_t.MAX_VALUE;
   }

    void setAccessTime(long time) {
   }

   public ReferenceEntry<K, V> getNextInAccessQueue() {
      return this.nextAccess;
   }

    void setNextInAccessQueue(V> next) {
      this.nextAccess = next;
   }

   public ReferenceEntry<K, V> getPreviousInAccessQueue() {
      return this.previousAccess;
   }

    void setPreviousInAccessQueue(V> previous) {
      this.previousAccess = previous;
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
