#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/list/array/TIntArrayList.h"

namespace gnu {
namespace trove {
namespace set {
namespace hash {


class TLinkedHashSet {
public:
   TLinkedHashSet$1(TLinkedHashSet var1, int x0) {
      super(x0);
      this.this$0 = var1;
   }

    void ensureCapacity(int capacity) {
      if (capacity > this._data.length) {
    int newCap = Math.max(this.this$0._set.length, capacity);
         int[] tmp = new int[newCap];
         System.arraycopy(this._data, 0, tmp, 0, this._data.length);
         this._data = tmp;
      }
   }
}
} // namespace hash
} // namespace set
} // namespace trove
} // namespace gnu
