#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/cache/LocalCache/LoadingValueReference.h"
#include "com/google/common/cache/LocalCache/Segment.h"
#include "com/google/common/util/concurrent/ListenableFuture.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace cache {


class LocalCache {
public:
   LocalCache$Segment$1(Segment var1, Object var2, int var3, LoadingValueReference var4, ListenableFuture var5) {
      this.this$0 = var1;
      this.val$key = var2;
      this.val$hash = var3;
      this.val$loadingValueReference = var4;
      this.val$loadingFuture = var5;
   }

    void run() {
      try {
         this.this$0.getAndRecordStats(this.val$key, this.val$hash, this.val$loadingValueReference, this.val$loadingFuture);
      } catch (Throwable var2) {
         LocalCache.logger.log(Level.WARNING, "Exception thrown during refresh", var2);
         this.val$loadingValueReference.setException(var2);
      }
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
