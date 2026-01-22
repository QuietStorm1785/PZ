#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Optional.h"
#include "com/google/common/collect/BinaryTreeTraverser/1.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class BinaryTreeTraverser {
public:
    bool doneLeft;
    bool doneRight;

   BinaryTreeTraverser$1$1(1 var1) {
      this.this$1 = var1;
   }

    T computeNext() {
      if (!this.doneLeft) {
         this.doneLeft = true;
         Optional<T> left = this.this$1.this$0.leftChild(this.this$1.val$root);
         if (left.isPresent()) {
            return (T)left.get();
         }
      }

      if (!this.doneRight) {
         this.doneRight = true;
         Optional<T> right = this.this$1.this$0.rightChild(this.this$1.val$root);
         if (right.isPresent()) {
            return (T)right.get();
         }
      }

      return (T)this.endOfData();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
