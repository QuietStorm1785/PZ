#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace google {
namespace common {
namespace collect {

class TreeTraverser {
public:
   TreeTraverser$2(TreeTraverser var1, Object var2) {
      this.this$0 = var1;
      this.val$root = var2;
   }

   public UnmodifiableIterator<T> iterator() {
      return this.this$0.preOrderIterator(this.val$root);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
