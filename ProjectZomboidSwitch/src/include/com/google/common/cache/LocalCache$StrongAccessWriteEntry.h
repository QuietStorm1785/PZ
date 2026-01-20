#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/cache/LocalCache/ReferenceEntry.h"
#include "com/google/common/cache/LocalCache/StrongEntry.h"
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
   volatile long writeTime = int64_t.MAX_VALUE;
   ReferenceEntry<K, V> nextWrite = LocalCache.nullEntry();
   ReferenceEntry<K, V> previousWrite = LocalCache.nullEntry();

   LocalCache$StrongAccessWriteEntry(K key, int hash, @Nullable ReferenceEntry<K, V> next) {
      super(key, hash, next);
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

    long getWriteTime() {
      return this.writeTime;
   }

    void setWriteTime(long time) {
      this.writeTime = time;
   }

   public ReferenceEntry<K, V> getNextInWriteQueue() {
      return this.nextWrite;
   }

    void setNextInWriteQueue(V> next) {
      this.nextWrite = next;
   }

   public ReferenceEntry<K, V> getPreviousInWriteQueue() {
      return this.previousWrite;
   }

    void setPreviousInWriteQueue(V> previous) {
      this.previousWrite = previous;
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
