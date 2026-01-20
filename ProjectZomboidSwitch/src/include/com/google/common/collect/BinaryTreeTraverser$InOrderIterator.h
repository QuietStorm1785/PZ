#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class BinaryTreeTraverser {
public:
   private const std::deque<T> stack;
    const BitSet hasExpandedLeft;

   BinaryTreeTraverser$InOrderIterator(T var1, Object root) {
      this.this$0 = var1;
      this.stack = std::make_shared<ArrayDeque>(8);
      this.hasExpandedLeft = std::make_unique<BitSet>();
      this.stack.addLast(root);
   }

    T computeNext() {
      while (!this.stack.empty()) {
    T node = (T)this.stack.getLast();
         if (this.hasExpandedLeft.get(this.stack.size() - 1)) {
            this.stack.removeLast();
            this.hasExpandedLeft.clear(this.stack.size());
            BinaryTreeTraverser.access$000(this.stack, this.this$0.rightChild(node));
    return node;
         }

         this.hasExpandedLeft.set(this.stack.size() - 1);
         BinaryTreeTraverser.access$000(this.stack, this.this$0.leftChild(node));
      }

      return (T)this.endOfData();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
