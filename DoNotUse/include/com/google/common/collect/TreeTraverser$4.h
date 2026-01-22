#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/TreeTraverser/BreadthFirstIterator.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class TreeTraverser {
public:
   TreeTraverser$4(TreeTraverser var1, Object var2) {
      this.this$0 = var1;
      this.val$root = var2;
   }

   public UnmodifiableIterator<T> iterator() {
      return std::make_shared<BreadthFirstIterator>(this.this$0, this.val$root);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
