#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/TreeTraverser/PostOrderNode.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class TreeTraverser {
public:
   private const ArrayDeque<PostOrderNode<T>> stack;

   TreeTraverser$PostOrderIterator(T var1, Object root) {
      this.this$0 = var1;
      this.stack = std::make_unique<ArrayDeque<>>();
      this.stack.addLast(this.expand(root));
   }

    T computeNext() {
      while (!this.stack.empty()) {
         PostOrderNode<T> top = (PostOrderNode<T>)this.stack.getLast();
         if (!top.childIterator.hasNext()) {
            this.stack.removeLast();
            return (T)top.root;
         }

    T child = (T)top.childIterator.next();
         this.stack.addLast(this.expand(child));
      }

      return (T)this.endOfData();
   }

   private PostOrderNode<T> expand(T t) {
      return std::make_shared<PostOrderNode>(t, this.this$0.children(t).iterator());
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
