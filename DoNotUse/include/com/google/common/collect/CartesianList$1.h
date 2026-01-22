#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class CartesianList {
public:
   CartesianList$1(CartesianList var1, int var2) {
      this.this$0 = var1;
      this.val$index = var2;
   }

    int size() {
      return CartesianList.access$000(this.this$0).size();
   }

    E get(int axis) {
      Preconditions.checkElementIndex(axis, this.size());
    int axisIndex = CartesianList.access$100(this.this$0, this.val$index, axis);
      return (E)((List)CartesianList.access$000(this.this$0).get(axis)).get(axisIndex);
   }

    bool isPartialView() {
    return true;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
