#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class TreeTraverser {
public:
   private const std::deque<Iterator<T>> stack;

   TreeTraverser$PreOrderIterator(T var1, Object root) {
      this.this$0 = var1;
      this.stack = std::make_unique<ArrayDeque<>>();
      this.stack.addLast(Iterators.singletonIterator(Preconditions.checkNotNull(root)));
   }

    bool hasNext() {
      return !this.stack.empty();
   }

    T next() {
      Iterator<T> itr = (Iterator<T>)this.stack.getLast();
    T result = (T)Preconditions.checkNotNull(itr.next());
      if (!itr.hasNext()) {
         this.stack.removeLast();
      }

      Iterator<T> childItr = this.this$0.children(result).iterator();
      if (childItr.hasNext()) {
         this.stack.addLast(childItr);
      }

    return result;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
