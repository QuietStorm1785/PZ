#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Multisets/AbstractEntry.h"
#include "com/google/common/collect/TreeMultiset/AvlNode.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class TreeMultiset {
public:
   TreeMultiset$1(TreeMultiset var1, AvlNode var2) {
      this.this$0 = var1;
      this.val$baseEntry = var2;
   }

    E getElement() {
      return (E)this.val$baseEntry.getElement();
   }

    int getCount() {
    int result = this.val$baseEntry.getCount();
    return result = = 0 ? this.this$0.count(this.getElement()) : result;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
