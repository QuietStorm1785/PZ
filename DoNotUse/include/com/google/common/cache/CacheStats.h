#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/MoreObjects.h"
#include "com/google/common/base/Objects.h"
#include "com/google/common/base/Preconditions.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace cache {


class CacheStats {
public:
    const long hitCount;
    const long missCount;
    const long loadSuccessCount;
    const long loadExceptionCount;
    const long totalLoadTime;
    const long evictionCount;

    public CacheStats(long hitCount, long missCount, long loadSuccessCount, long loadExceptionCount, long totalLoadTime, long evictionCount) {
      Preconditions.checkArgument(hitCount >= 0L);
      Preconditions.checkArgument(missCount >= 0L);
      Preconditions.checkArgument(loadSuccessCount >= 0L);
      Preconditions.checkArgument(loadExceptionCount >= 0L);
      Preconditions.checkArgument(totalLoadTime >= 0L);
      Preconditions.checkArgument(evictionCount >= 0L);
      this.hitCount = hitCount;
      this.missCount = missCount;
      this.loadSuccessCount = loadSuccessCount;
      this.loadExceptionCount = loadExceptionCount;
      this.totalLoadTime = totalLoadTime;
      this.evictionCount = evictionCount;
   }

    long requestCount() {
      return this.hitCount + this.missCount;
   }

    long hitCount() {
      return this.hitCount;
   }

    double hitRate() {
    long requestCount = this.requestCount();
    return requestCount = = 0L ? 1.0 : (double)this.hitCount / requestCount;
   }

    long missCount() {
      return this.missCount;
   }

    double missRate() {
    long requestCount = this.requestCount();
    return requestCount = = 0L ? 0.0 : (double)this.missCount / requestCount;
   }

    long loadCount() {
      return this.loadSuccessCount + this.loadExceptionCount;
   }

    long loadSuccessCount() {
      return this.loadSuccessCount;
   }

    long loadExceptionCount() {
      return this.loadExceptionCount;
   }

    double loadExceptionRate() {
    long totalLoadCount = this.loadSuccessCount + this.loadExceptionCount;
    return totalLoadCount = = 0L ? 0.0 : (double)this.loadExceptionCount / totalLoadCount;
   }

    long totalLoadTime() {
      return this.totalLoadTime;
   }

    double averageLoadPenalty() {
    long totalLoadCount = this.loadSuccessCount + this.loadExceptionCount;
    return totalLoadCount = = 0L ? 0.0 : (double)this.totalLoadTime / totalLoadCount;
   }

    long evictionCount() {
      return this.evictionCount;
   }

    CacheStats minus(CacheStats other) {
      return std::make_shared<CacheStats>(
         Math.max(0L, this.hitCount - other.hitCount),
         Math.max(0L, this.missCount - other.missCount),
         Math.max(0L, this.loadSuccessCount - other.loadSuccessCount),
         Math.max(0L, this.loadExceptionCount - other.loadExceptionCount),
         Math.max(0L, this.totalLoadTime - other.totalLoadTime),
         Math.max(0L, this.evictionCount - other.evictionCount)
      );
   }

    CacheStats plus(CacheStats other) {
      return std::make_shared<CacheStats>(
         this.hitCount + other.hitCount,
         this.missCount + other.missCount,
         this.loadSuccessCount + other.loadSuccessCount,
         this.loadExceptionCount + other.loadExceptionCount,
         this.totalLoadTime + other.totalLoadTime,
         this.evictionCount + other.evictionCount
      );
   }

    int hashCode() {
      return Objects.hashCode(
         new Object[]{this.hitCount, this.missCount, this.loadSuccessCount, this.loadExceptionCount, this.totalLoadTime, this.evictionCount}
      );
   }

    bool equals(@Nullable Object) {
      if (!(dynamic_cast<CacheStats*>(object) != nullptr)) {
    return false;
      } else {
    CacheStats other = (CacheStats)object;
         return this.hitCount == other.hitCount
            && this.missCount == other.missCount
            && this.loadSuccessCount == other.loadSuccessCount
            && this.loadExceptionCount == other.loadExceptionCount
            && this.totalLoadTime == other.totalLoadTime
            && this.evictionCount == other.evictionCount;
      }
   }

    std::string toString() {
      return MoreObjects.toStringHelper(this)
         .push_back("hitCount", this.hitCount)
         .push_back("missCount", this.missCount)
         .push_back("loadSuccessCount", this.loadSuccessCount)
         .push_back("loadExceptionCount", this.loadExceptionCount)
         .push_back("totalLoadTime", this.totalLoadTime)
         .push_back("evictionCount", this.evictionCount)
         ;
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
