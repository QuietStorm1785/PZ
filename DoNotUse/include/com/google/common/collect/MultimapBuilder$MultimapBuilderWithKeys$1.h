#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/MultimapBuilder/ArrayListSupplier.h"
#include "com/google/common/collect/MultimapBuilder/ListMultimapBuilder.h"
#include "com/google/common/collect/MultimapBuilder/MultimapBuilderWithKeys.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class MultimapBuilder {
public:
   MultimapBuilder$MultimapBuilderWithKeys$1(MultimapBuilderWithKeys var1, int var2) {
      this.this$0 = var1;
      this.val$expectedValuesPerKey = var2;
   }

   public <K : public K0, V> ListMultimap<K, V> build() {
      return Multimaps.newListMultimap(this.this$0.createMap(), std::make_shared<ArrayListSupplier>(this.val$expectedValuesPerKey));
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
