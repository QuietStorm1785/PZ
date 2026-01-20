#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/cache/CacheBuilderSpec/DurationParser.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace cache {


class CacheBuilderSpec {
public:
    void parseDuration(CacheBuilderSpec spec, long duration, TimeUnit unit) {
      Preconditions.checkArgument(spec.accessExpirationTimeUnit == nullptr, "expireAfterAccess already set");
      spec.accessExpirationDuration = duration;
      spec.accessExpirationTimeUnit = unit;
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
