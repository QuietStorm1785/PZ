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
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "com/google/j2objc/annotations/Weak.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class MinMaxPriorityQueue {
public:
   const Ordering<E> ordering;
   MinMaxPriorityQueue<E>.Heap otherHeap;

   MinMaxPriorityQueue$Heap(Ordering<E> var1, Ordering ordering) {
      this.this$0 = var1;
      this.ordering = ordering;
   }

    int compareElements(int a, int b) {
      return this.ordering.compare(this.this$0.elementData(a), this.this$0.elementData(b));
   }

   MoveDesc<E> tryCrossOverAndBubbleUp(int removeIndex, int vacated, E toTrickle) {
    int crossOver = this.crossOver(vacated, toTrickle);
      if (crossOver == vacated) {
    return nullptr;
      } else {
    E parent;
         if (crossOver < removeIndex) {
            parent = (E)this.this$0.elementData(removeIndex);
         } else {
            parent = (E)this.this$0.elementData(this.getParentIndex(removeIndex));
         }

         return this.otherHeap.bubbleUpAlternatingLevels(crossOver, toTrickle) < removeIndex ? std::make_shared<MoveDesc>(toTrickle, parent) : nullptr;
      }
   }

    void bubbleUp(int index, E x) {
    int crossOver = this.crossOverUp(index, x);
      MinMaxPriorityQueue<E>.Heap heap;
      if (crossOver == index) {
         heap = this;
      } else {
         index = crossOver;
         heap = this.otherHeap;
      }

      heap.bubbleUpAlternatingLevels(index, x);
   }

    int bubbleUpAlternatingLevels(int index, E x) {
      while (index > 2) {
    int grandParentIndex = this.getGrandparentIndex(index);
    E e = (E)this.this$0.elementData(grandParentIndex);
         if (this.ordering.compare(e, x) > 0) {
            MinMaxPriorityQueue.access$500(this.this$0)[index] = e;
            index = grandParentIndex;
            continue;
         }
         break;
      }

      MinMaxPriorityQueue.access$500(this.this$0)[index] = x;
    return index;
   }

    int findMin(int index, int len) {
      if (index >= MinMaxPriorityQueue.access$600(this.this$0)) {
         return -1;
      } else {
         Preconditions.checkState(index > 0);
    int limit = Math.min(index, MinMaxPriorityQueue.access$600(this.this$0) - len) + len;
    int minIndex = index;

         for (int i = index + 1; i < limit; i++) {
            if (this.compareElements(i, minIndex) < 0) {
               minIndex = i;
            }
         }

    return minIndex;
      }
   }

    int findMinChild(int index) {
      return this.findMin(this.getLeftChildIndex(index), 2);
   }

    int findMinGrandChild(int index) {
    int leftChildIndex = this.getLeftChildIndex(index);
      return leftChildIndex < 0 ? -1 : this.findMin(this.getLeftChildIndex(leftChildIndex), 4);
   }

    int crossOverUp(int index, E x) {
      if (index == 0) {
         MinMaxPriorityQueue.access$500(this.this$0)[0] = x;
    return 0;
      } else {
    int parentIndex = this.getParentIndex(index);
    E parentElement = (E)this.this$0.elementData(parentIndex);
         if (parentIndex != 0) {
    int grandparentIndex = this.getParentIndex(parentIndex);
    int uncleIndex = this.getRightChildIndex(grandparentIndex);
            if (uncleIndex != parentIndex && this.getLeftChildIndex(uncleIndex) >= MinMaxPriorityQueue.access$600(this.this$0)) {
    E uncleElement = (E)this.this$0.elementData(uncleIndex);
               if (this.ordering.compare(uncleElement, parentElement) < 0) {
                  parentIndex = uncleIndex;
                  parentElement = uncleElement;
               }
            }
         }

         if (this.ordering.compare(parentElement, x) < 0) {
            MinMaxPriorityQueue.access$500(this.this$0)[index] = parentElement;
            MinMaxPriorityQueue.access$500(this.this$0)[parentIndex] = x;
    return parentIndex;
         } else {
            MinMaxPriorityQueue.access$500(this.this$0)[index] = x;
    return index;
         }
      }
   }

    int getCorrectLastElement(E actualLastElement) {
    int parentIndex = this.getParentIndex(MinMaxPriorityQueue.access$600(this.this$0));
      if (parentIndex != 0) {
    int grandparentIndex = this.getParentIndex(parentIndex);
    int uncleIndex = this.getRightChildIndex(grandparentIndex);
         if (uncleIndex != parentIndex && this.getLeftChildIndex(uncleIndex) >= MinMaxPriorityQueue.access$600(this.this$0)) {
    E uncleElement = (E)this.this$0.elementData(uncleIndex);
            if (this.ordering.compare(uncleElement, actualLastElement) < 0) {
               MinMaxPriorityQueue.access$500(this.this$0)[uncleIndex] = actualLastElement;
               MinMaxPriorityQueue.access$500(this.this$0)[MinMaxPriorityQueue.access$600(this.this$0)] = uncleElement;
    return uncleIndex;
            }
         }
      }

      return MinMaxPriorityQueue.access$600(this.this$0);
   }

    int crossOver(int index, E x) {
    int minChildIndex = this.findMinChild(index);
      if (minChildIndex > 0 && this.ordering.compare(this.this$0.elementData(minChildIndex), x) < 0) {
         MinMaxPriorityQueue.access$500(this.this$0)[index] = this.this$0.elementData(minChildIndex);
         MinMaxPriorityQueue.access$500(this.this$0)[minChildIndex] = x;
    return minChildIndex;
      } else {
         return this.crossOverUp(index, x);
      }
   }

    int fillHoleAt(int index) {
    int minGrandchildIndex;
      while ((minGrandchildIndex = this.findMinGrandChild(index)) > 0) {
         MinMaxPriorityQueue.access$500(this.this$0)[index] = this.this$0.elementData(minGrandchildIndex);
         index = minGrandchildIndex;
      }

    return index;
   }

    bool verifyIndex(int i) {
      if (this.getLeftChildIndex(i) < MinMaxPriorityQueue.access$600(this.this$0) && this.compareElements(i, this.getLeftChildIndex(i)) > 0) {
    return false;
      } else if (this.getRightChildIndex(i) < MinMaxPriorityQueue.access$600(this.this$0) && this.compareElements(i, this.getRightChildIndex(i)) > 0) {
    return false;
      } else {
         return i > 0 && this.compareElements(i, this.getParentIndex(i)) > 0 ? false : i <= 2 || this.compareElements(this.getGrandparentIndex(i), i) <= 0;
      }
   }

    int getLeftChildIndex(int i) {
      return i * 2 + 1;
   }

    int getRightChildIndex(int i) {
      return i * 2 + 2;
   }

    int getParentIndex(int i) {
      return (i - 1) / 2;
   }

    int getGrandparentIndex(int i) {
      return this.getParentIndex(this.getParentIndex(i));
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
