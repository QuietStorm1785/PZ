#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/MultimapBuilder/MultimapBuilderWithKeys.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class MultimapBuilder {
public:
   MultimapBuilder$1(int var1) {
      this.val$expectedKeys = var1;
   }

   <K, V> Map<K, Collection<V>> createMap() {
      return Maps.newHashMapWithExpectedSize(this.val$expectedKeys);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
