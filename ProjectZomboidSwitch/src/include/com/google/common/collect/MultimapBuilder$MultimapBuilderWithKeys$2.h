#pragma once
#include <list>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/MultimapBuilder/LinkedListSupplier.h"
#include "com/google/common/collect/MultimapBuilder/ListMultimapBuilder.h"
#include "com/google/common/collect/MultimapBuilder/MultimapBuilderWithKeys.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class MultimapBuilder {
public:
   MultimapBuilder$MultimapBuilderWithKeys$2(MultimapBuilderWithKeys var1) {
      this.this$0 = var1;
   }

   public <K : public K0, V> ListMultimap<K, V> build() {
      return Multimaps.newListMultimap(this.this$0.createMap(), LinkedListSupplier.instance());
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
