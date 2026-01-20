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

   BinaryTreeTraverser$PreOrderIterator(T var1, Object root) {
      this.this$0 = var1;
      this.stack = std::make_shared<ArrayDeque>(8);
      this.stack.addLast(root);
   }

    bool hasNext() {
      return !this.stack.empty();
   }

    T next() {
    T result = (T)this.stack.removeLast();
      BinaryTreeTraverser.access$000(this.stack, this.this$0.rightChild(result));
      BinaryTreeTraverser.access$000(this.stack, this.this$0.leftChild(result));
    return result;
   }

    T peek() {
      return (T)this.stack.getLast();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
