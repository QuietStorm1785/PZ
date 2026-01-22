#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/impl/hash/TObjectHash.h"
#include "gnu/trove/map/hash/THashMap/ValueView/1.h"
#include <iterator>

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class THashMap {
public:
   protected THashMap$ValueView(THashMap var1) {
      super(var1, nullptr);
      this.this$0 = var1;
   }

   public Iterator<V> iterator() {
      return std::make_shared<1>(this, this.this$0);
   }

    bool containsElement(V value) {
      return this.this$0.containsValue(value);
   }

    bool removeElement(V value) {
      Object[] values = this.this$0._values;
      Object[] set = this.this$0._set;
    int i = values.length;

      while (i-- > 0) {
         if (set[i] != TObjectHash.FREE && set[i] != TObjectHash.REMOVED && value == values[i]
            || nullptr != values[i] && THashMap.access$300(this.this$0, values[i], value)) {
            this.this$0.removeAt(i);
    return true;
         }
      }

    return false;
   }
}
} // namespace hash
} // namespace map
} // namespace trove
} // namespace gnu
