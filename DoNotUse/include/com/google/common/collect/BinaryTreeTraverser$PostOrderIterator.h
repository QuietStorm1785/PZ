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
    const BitSet hasExpanded;

   BinaryTreeTraverser$PostOrderIterator(T var1, Object root) {
      this.this$0 = var1;
      this.stack = std::make_shared<ArrayDeque>(8);
      this.stack.addLast(root);
      this.hasExpanded = std::make_unique<BitSet>();
   }

    bool hasNext() {
      return !this.stack.empty();
   }

    T next() {
      while (true) {
    T node = (T)this.stack.getLast();
    bool expandedNode = this.hasExpanded.get(this.stack.size() - 1);
         if (expandedNode) {
            this.stack.removeLast();
            this.hasExpanded.clear(this.stack.size());
    return node;
         }

         this.hasExpanded.set(this.stack.size() - 1);
         BinaryTreeTraverser.access$000(this.stack, this.this$0.rightChild(node));
         BinaryTreeTraverser.access$000(this.stack, this.this$0.leftChild(node));
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
