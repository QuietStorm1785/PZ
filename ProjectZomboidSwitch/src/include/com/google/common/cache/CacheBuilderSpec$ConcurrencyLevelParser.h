#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/cache/CacheBuilderSpec/IntegerParser.h"

namespace com {
namespace google {
namespace common {
namespace cache {


class CacheBuilderSpec {
public:
    void parseInteger(CacheBuilderSpec spec, int value) {
      Preconditions.checkArgument(spec.concurrencyLevel == nullptr, "concurrency level was already set to ", spec.concurrencyLevel);
      spec.concurrencyLevel = value;
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
