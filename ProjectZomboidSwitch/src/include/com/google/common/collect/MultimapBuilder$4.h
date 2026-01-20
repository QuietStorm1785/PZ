#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/MultimapBuilder/MultimapBuilderWithKeys.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class MultimapBuilder {
public:
   MultimapBuilder$4(Class var1) {
      this.val$keyClass = var1;
   }

   <K : public K0, V> Map<K, Collection<V>> createMap() {
      return new EnumMap<>(this.val$keyClass);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
