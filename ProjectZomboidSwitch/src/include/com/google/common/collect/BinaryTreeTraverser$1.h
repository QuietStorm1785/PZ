#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/BinaryTreeTraverser/1/1.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class BinaryTreeTraverser {
public:
   BinaryTreeTraverser$1(BinaryTreeTraverser var1, Object var2) {
      this.this$0 = var1;
      this.val$root = var2;
   }

   public Iterator<T> iterator() {
      return std::make_shared<1>(this);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
