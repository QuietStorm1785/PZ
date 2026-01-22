#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Supplier.h"
#include "com/google/common/cache/AbstractCache/SimpleStatsCounter.h"
#include "com/google/common/cache/AbstractCache/StatsCounter.h"

namespace com {
namespace google {
namespace common {
namespace cache {


class CacheBuilder {
public:
    StatsCounter get() {
      return std::make_unique<SimpleStatsCounter>();
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
