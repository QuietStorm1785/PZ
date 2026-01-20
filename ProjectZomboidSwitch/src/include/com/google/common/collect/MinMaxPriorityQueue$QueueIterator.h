#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/MinMaxPriorityQueue/MoveDesc.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class MinMaxPriorityQueue {
public:
    int cursor;
    int expectedModCount;
   private std::queue<E> forgetMeNot;
   private List<E> skipMe;
    E lastFromForgetMeNot;
    bool canRemove;

   private MinMaxPriorityQueue$QueueIterator(MinMaxPriorityQueue var1) {
      this.this$0 = var1;
      this.cursor = -1;
      this.expectedModCount = MinMaxPriorityQueue.access$700(this.this$0);
   }

    bool hasNext() {
      this.checkModCount();
      return this.nextNotInSkipMe(this.cursor + 1) < this.this$0.size() || this.forgetMeNot != nullptr && !this.forgetMeNot.empty();
   }

    E next() {
      this.checkModCount();
    int tempCursor = this.nextNotInSkipMe(this.cursor + 1);
      if (tempCursor < this.this$0.size()) {
         this.cursor = tempCursor;
         this.canRemove = true;
         return (E)this.this$0.elementData(this.cursor);
      } else {
         if (this.forgetMeNot != nullptr) {
            this.cursor = this.this$0.size();
            this.lastFromForgetMeNot = (E)this.forgetMeNot.poll();
            if (this.lastFromForgetMeNot != nullptr) {
               this.canRemove = true;
               return this.lastFromForgetMeNot;
            }
         }

         throw NoSuchElementException("iterator moved past last element in queue.");
      }
   }

    void remove() {
      CollectPreconditions.checkRemove(this.canRemove);
      this.checkModCount();
      this.canRemove = false;
      this.expectedModCount++;
      if (this.cursor < this.this$0.size()) {
         MoveDesc<E> moved = this.this$0.removeAt(this.cursor);
         if (moved != nullptr) {
            if (this.forgetMeNot == nullptr) {
               this.forgetMeNot = std::make_unique<ArrayDeque>();
               this.skipMe = new std::vector(3);
            }

            this.forgetMeNot.push_back(moved.toTrickle);
            this.skipMe.push_back(moved.replaced);
         }

         this.cursor--;
      } else {
         Preconditions.checkState(this.removeExact(this.lastFromForgetMeNot));
         this.lastFromForgetMeNot = nullptr;
      }
   }

    bool containsExact(Iterable<E> elements, E target) {
    for (auto& element : elements)         if (element == target) {
    return true;
         }
      }

    return false;
   }

    bool removeExact(void* target) {
      for (int i = 0; i < MinMaxPriorityQueue.access$600(this.this$0); i++) {
         if (MinMaxPriorityQueue.access$500(this.this$0)[i] == target) {
            this.this$0.removeAt(i);
    return true;
         }
      }

    return false;
   }

    void checkModCount() {
      if (MinMaxPriorityQueue.access$700(this.this$0) != this.expectedModCount) {
         throw std::make_unique<ConcurrentModificationException>();
      }
   }

    int nextNotInSkipMe(int c) {
      if (this.skipMe != nullptr) {
         while (c < this.this$0.size() && this.containsExact(this.skipMe, this.this$0.elementData(c))) {
            c++;
         }
      }

    return c;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
