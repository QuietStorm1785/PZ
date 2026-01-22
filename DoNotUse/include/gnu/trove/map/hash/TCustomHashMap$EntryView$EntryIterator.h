#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/iterator/hash/TObjectHashIterator.h"
#include "gnu/trove/map/hash/TCustomHashMap/Entry.h"

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class TCustomHashMap {
public:
   TCustomHashMap$EntryView$EntryIterator(TCustomHashMap<K, V> var1, TCustomHashMap map) {
      super(map);
      this.this$1 = var1;
   }

   public TCustomHashMap<K, V>.Entry objectAtIndex(int index) {
      return std::make_shared<Entry>(this.this$1.this$0, this.this$1.this$0._set[index], this.this$1.this$0._values[index], index);
   }
}
} // namespace hash
} // namespace map
} // namespace trove
} // namespace gnu
