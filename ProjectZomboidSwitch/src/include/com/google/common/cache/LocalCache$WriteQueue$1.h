#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/cache/LocalCache/AbstractReferenceEntry.h"
#include "com/google/common/cache/LocalCache/ReferenceEntry.h"
#include "com/google/common/cache/LocalCache/WriteQueue.h"

namespace com {
namespace google {
namespace common {
namespace cache {


class LocalCache {
public:
   ReferenceEntry<K, V> nextWrite;
   ReferenceEntry<K, V> previousWrite;

   LocalCache$WriteQueue$1(WriteQueue var1) {
      this.this$0 = var1;
      this.nextWrite = this;
      this.previousWrite = this;
   }

    long getWriteTime() {
      return int64_t.MAX_VALUE;
   }

    void setWriteTime(long time) {
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
