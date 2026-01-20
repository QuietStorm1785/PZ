#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class MinMaxPriorityQueue {
public:
    static const int UNSET_EXPECTED_SIZE = -1;
   private const Comparator<B> comparator;
    int expectedSize = -1;
    int maximumSize = int.MAX_VALUE;

   private MinMaxPriorityQueue$Builder(Comparator<B> comparator) {
      this.comparator = (Comparator<B>)Preconditions.checkNotNull(comparator);
   }

   public MinMaxPriorityQueue$Builder<B> expectedSize(int expectedSize) {
      Preconditions.checkArgument(expectedSize >= 0);
      this.expectedSize = expectedSize;
    return this;
   }

   public MinMaxPriorityQueue$Builder<B> maximumSize(int maximumSize) {
      Preconditions.checkArgument(maximumSize > 0);
      this.maximumSize = maximumSize;
    return this;
   }

   public <T : public B> MinMaxPriorityQueue<T> create() {
      return this.create(Collections.emptySet());
   }

   public <T : public B> MinMaxPriorityQueue<T> create(Iterable<? : public T> initialContents) {
      MinMaxPriorityQueue<T> queue = std::make_shared<MinMaxPriorityQueue>(
         this, MinMaxPriorityQueue.initialQueueSize(this.expectedSize, this.maximumSize, initialContents), nullptr
      );

    for (auto& element : initialContents)         queue.offer(element);
      }

    return queue;
   }

   private <T : public B> Ordering<T> ordering() {
      return Ordering.from(this.comparator);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
