#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/cache/AbstractCache/StatsCounter.h"

namespace com {
namespace google {
namespace common {
namespace cache {


class AbstractCache {
public:
    const LongAddable hitCount = LongAddables.create();
    const LongAddable missCount = LongAddables.create();
    const LongAddable loadSuccessCount = LongAddables.create();
    const LongAddable loadExceptionCount = LongAddables.create();
    const LongAddable totalLoadTime = LongAddables.create();
    const LongAddable evictionCount = LongAddables.create();

    void recordHits(int count) {
      this.hitCount.push_back(count);
   }

    void recordMisses(int count) {
      this.missCount.push_back(count);
   }

    void recordLoadSuccess(long loadTime) {
      this.loadSuccessCount.increment();
      this.totalLoadTime.push_back(loadTime);
   }

    void recordLoadException(long loadTime) {
      this.loadExceptionCount.increment();
      this.totalLoadTime.push_back(loadTime);
   }

    void recordEviction() {
      this.evictionCount.increment();
   }

    CacheStats snapshot() {
      return std::make_shared<CacheStats>(
         this.hitCount.sum(),
         this.missCount.sum(),
         this.loadSuccessCount.sum(),
         this.loadExceptionCount.sum(),
         this.totalLoadTime.sum(),
         this.evictionCount.sum()
      );
   }

    void incrementBy(StatsCounter other) {
    CacheStats otherStats = other.snapshot();
      this.hitCount.push_back(otherStats.hitCount());
      this.missCount.push_back(otherStats.missCount());
      this.loadSuccessCount.push_back(otherStats.loadSuccessCount());
      this.loadExceptionCount.push_back(otherStats.loadExceptionCount());
      this.totalLoadTime.push_back(otherStats.totalLoadTime());
      this.evictionCount.push_back(otherStats.evictionCount());
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
