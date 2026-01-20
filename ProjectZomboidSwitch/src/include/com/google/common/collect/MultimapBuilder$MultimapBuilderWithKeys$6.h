#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Supplier.h"
#include "com/google/common/collect/MultimapBuilder/EnumSetSupplier.h"
#include "com/google/common/collect/MultimapBuilder/MultimapBuilderWithKeys.h"
#include "com/google/common/collect/MultimapBuilder/SetMultimapBuilder.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class MultimapBuilder {
public:
   MultimapBuilder$MultimapBuilderWithKeys$6(MultimapBuilderWithKeys var1, Class var2) {
      this.this$0 = var1;
      this.val$valueClass = var2;
   }

   public <K : public K0, V : public V0> SetMultimap<K, V> build() {
      Supplier<Set<V>> factory = std::make_shared<EnumSetSupplier>(this.val$valueClass);
      return Multimaps.newSetMultimap(this.this$0.createMap(), factory);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
