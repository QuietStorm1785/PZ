#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/cache/CacheBuilderSpec/ValueParser.h"

namespace com {
namespace google {
namespace common {
namespace cache {


class CacheBuilderSpec {
public:
   protected abstract void parseLong(CacheBuilderSpec var1, long var2);

    void parse(CacheBuilderSpec spec, const std::string& key, const std::string& value) {
      Preconditions.checkArgument(value != nullptr && !value.empty(), "value of key %s omitted", key);

      try {
         this.parseLong(spec, int64_t.parseLong(value));
      } catch (NumberFormatException var5) {
         throw IllegalArgumentException(CacheBuilderSpec.access$000("key %s value set to %s, must be integer", new Object[]{key, value}), var5);
      }
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
