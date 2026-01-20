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


class CacheBuilder {
public:
    void recordHits(int count) {
   }

    void recordMisses(int count) {
   }

    void recordLoadSuccess(long loadTime) {
   }

    void recordLoadException(long loadTime) {
   }

    void recordEviction() {
   }

    CacheStats snapshot() {
      return CacheBuilder.EMPTY_STATS;
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
