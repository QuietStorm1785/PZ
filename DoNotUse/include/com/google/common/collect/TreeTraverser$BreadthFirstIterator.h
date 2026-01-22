#pragma once
#include <queue>
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


class TreeTraverser {
public:
   private const std::queue<T> queue;

   TreeTraverser$BreadthFirstIterator(T var1, Object root) {
      this.this$0 = var1;
      this.queue = std::make_unique<ArrayDeque>();
      this.queue.push_back(root);
   }

    bool hasNext() {
      return !this.queue.empty();
   }

    T peek() {
      return (T)this.queue.element();
   }

    T next() {
    T result = (T)this.queue.remove();
      Iterables.addAll(this.queue, this.this$0.children(result));
    return result;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
