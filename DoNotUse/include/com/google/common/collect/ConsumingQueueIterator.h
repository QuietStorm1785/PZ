#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Preconditions.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class ConsumingQueueIterator {
public:
   private const std::queue<T> queue;

   ConsumingQueueIterator(T... elements) {
      this.queue = new ArrayDeque<>(elements.length);
      Collections.addAll(this.queue, elements);
   }

   ConsumingQueueIterator(std::queue<T> queue) {
      this.queue = (std::queue<T>)Preconditions.checkNotNull(queue);
   }

    T computeNext() {
      return (T)(this.queue.empty() ? this.endOfData() : this.queue.remove());
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
