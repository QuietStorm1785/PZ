#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/impl/hash/TObjectHash.h"
#include "gnu/trove/iterator/hash/TObjectHashIterator.h"
#include "gnu/trove/map/hash/TCustomHashMap/ValueView.h"

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class TCustomHashMap {
public:
   TCustomHashMap$ValueView$1(ValueView var1, TObjectHash x0) {
      super(x0);
      this.this$1 = var1;
   }

    V objectAtIndex(int index) {
      return (V)this.this$1.this$0._values[index];
   }
}
} // namespace hash
} // namespace map
} // namespace trove
} // namespace gnu
