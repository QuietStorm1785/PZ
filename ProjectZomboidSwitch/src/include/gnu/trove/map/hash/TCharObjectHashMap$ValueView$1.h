#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/map/hash/TCharObjectHashMap/ValueView.h"
#include "gnu/trove/map/hash/TCharObjectHashMap/ValueView/TCharObjectValueHashIterator.h"

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class TCharObjectHashMap {
public:
   TCharObjectHashMap$ValueView$1(ValueView var1, TCharObjectHashMap x0) {
      super(var1, x0);
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
