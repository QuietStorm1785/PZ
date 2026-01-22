#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/MultimapBuilder/LinkedHashSetSupplier.h"
#include "com/google/common/collect/MultimapBuilder/MultimapBuilderWithKeys.h"
#include "com/google/common/collect/MultimapBuilder/SetMultimapBuilder.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class MultimapBuilder {
public:
   MultimapBuilder$MultimapBuilderWithKeys$4(MultimapBuilderWithKeys var1, int var2) {
      this.this$0 = var1;
      this.val$expectedValuesPerKey = var2;
   }

   public <K : public K0, V> SetMultimap<K, V> build() {
      return Multimaps.newSetMultimap(this.this$0.createMap(), std::make_shared<LinkedHashSetSupplier>(this.val$expectedValuesPerKey));
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
