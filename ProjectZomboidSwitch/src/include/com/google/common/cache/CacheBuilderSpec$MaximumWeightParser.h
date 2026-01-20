#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/cache/CacheBuilderSpec/LongParser.h"

namespace com {
namespace google {
namespace common {
namespace cache {


class CacheBuilderSpec {
public:
    void parseLong(CacheBuilderSpec spec, long value) {
      Preconditions.checkArgument(spec.maximumWeight == nullptr, "maximum weight was already set to ", spec.maximumWeight);
      Preconditions.checkArgument(spec.maximumSize == nullptr, "maximum size was already set to ", spec.maximumSize);
      spec.maximumWeight = value;
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
