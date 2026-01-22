#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/cache/LocalCache/ReferenceEntry.h"
#include "com/google/common/cache/LocalCache/WeakEntry.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace cache {


class LocalCache {
public:
   volatile long accessTime = int64_t.MAX_VALUE;
   ReferenceEntry<K, V> nextAccess = LocalCache.nullEntry();
   ReferenceEntry<K, V> previousAccess = LocalCache.nullEntry();

   LocalCache$WeakAccessEntry(ReferenceQueue<K> queue, K key, int hash, @Nullable ReferenceEntry<K, V> next) {
      super(queue, key, hash, next);
   }

    long getAccessTime() {
      return this.accessTime;
   }

    void setAccessTime(long time) {
      this.accessTime = time;
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
