#pragma once
#include <set>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/MultimapBuilder/MultimapBuilderWithKeys.h"
#include "com/google/common/collect/MultimapBuilder/SortedSetMultimapBuilder.h"
#include "com/google/common/collect/MultimapBuilder/TreeSetSupplier.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class MultimapBuilder {
public:
   MultimapBuilder$MultimapBuilderWithKeys$5(MultimapBuilderWithKeys var1, Comparator var2) {
      this.this$0 = var1;
      this.val$comparator = var2;
   }

   public <K : public K0, V : public V0> SortedSetMultimap<K, V> build() {
      return Multimaps.newSortedSetMultimap(this.this$0.createMap(), std::make_shared<TreeSetSupplier>(this.val$comparator));
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
