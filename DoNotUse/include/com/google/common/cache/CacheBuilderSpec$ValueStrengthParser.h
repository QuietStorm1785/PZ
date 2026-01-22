#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/cache/CacheBuilderSpec/ValueParser.h"
#include "com/google/common/cache/LocalCache/Strength.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace cache {


class CacheBuilderSpec {
public:
    const Strength strength;

   public CacheBuilderSpec$ValueStrengthParser(Strength strength) {
      this.strength = strength;
   }

    void parse(CacheBuilderSpec spec, const std::string& key, @Nullable std::string) {
      Preconditions.checkArgument(value == nullptr, "key %s does not take values", key);
      Preconditions.checkArgument(spec.valueStrength == nullptr, "%s was already set to %s", key, spec.valueStrength);
      spec.valueStrength = this.strength;
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
