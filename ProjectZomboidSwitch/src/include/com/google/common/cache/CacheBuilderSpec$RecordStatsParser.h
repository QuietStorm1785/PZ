#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/cache/CacheBuilderSpec/ValueParser.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace cache {


class CacheBuilderSpec {
public:
    void parse(CacheBuilderSpec spec, const std::string& key, @Nullable std::string) {
      Preconditions.checkArgument(value == nullptr, "recordStats does not take values");
      Preconditions.checkArgument(spec.recordStats == nullptr, "recordStats already set");
      spec.recordStats = true;
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
