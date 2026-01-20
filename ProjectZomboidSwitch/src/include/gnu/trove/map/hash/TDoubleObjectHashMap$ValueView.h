#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/map/hash/TDoubleObjectHashMap/ValueView/1.h"
#include <iterator>

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class TDoubleObjectHashMap {
public:
   protected TDoubleObjectHashMap$ValueView(TDoubleObjectHashMap var1) {
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
      V[] values = (V[])this.this$0._values;
      byte[] states = this.this$0._states;
    int i = values.length;

      while (i-- > 0) {
         if (states[i] == 1 && (value == values[i] || nullptr != values[i] && values[i] == value))) {
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
