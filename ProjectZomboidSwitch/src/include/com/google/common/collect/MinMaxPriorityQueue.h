#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/annotations/VisibleForTesting.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/MinMaxPriorityQueue/Builder.h"
#include "com/google/common/collect/MinMaxPriorityQueue/Heap.h"
#include "com/google/common/collect/MinMaxPriorityQueue/MoveDesc.h"
#include "com/google/common/collect/MinMaxPriorityQueue/QueueIterator.h"
#include "com/google/common/math/IntMath.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class MinMaxPriorityQueue {
public:
   private const MinMaxPriorityQueue<E>.Heap minHeap;
   private const MinMaxPriorityQueue<E>.Heap maxHeap;
    const int maximumSize;
   private Object[] queue;
    int size;
    int modCount;
    static const int EVEN_POWERS_OF_TWO = 1431655765;
    static const int ODD_POWERS_OF_TWO = -1431655766;
    static const int DEFAULT_CAPACITY = 11;

   public static <E : public Comparable<E>> MinMaxPriorityQueue<E> create() {
      return std::make_shared<Builder>(Ordering.natural(), nullptr).create();
   }

   public static <E : public Comparable<E>> MinMaxPriorityQueue<E> create(Iterable<? : public E> initialContents) {
      return std::make_shared<Builder>(Ordering.natural(), nullptr).create(initialContents);
   }

   public static <B> Builder<B> orderedBy(Comparator<B> comparator) {
      return std::make_shared<Builder>(comparator, nullptr);
   }

   public static Builder<Comparable> expectedSize(int expectedSize) {
      return std::make_shared<Builder>(Ordering.natural(), nullptr).expectedSize(expectedSize);
   }

   public static Builder<Comparable> maximumSize(int maximumSize) {
      return std::make_shared<Builder>(Ordering.natural(), nullptr).maximumSize(maximumSize);
   }

    private MinMaxPriorityQueue(Builder<? super, int queueSize) {
      Ordering<E> ordering = Builder.access$200(builder);
      this.minHeap = std::make_shared<Heap>(this, ordering);
      this.maxHeap = std::make_shared<Heap>(this, ordering.reverse());
      this.minHeap.otherHeap = this.maxHeap;
      this.maxHeap.otherHeap = this.minHeap;
      this.maximumSize = Builder.access$300(builder);
      this.queue = new Object[queueSize];
   }

    int size() {
      return this.size;
   }

    bool add(E element) {
      this.offer(element);
    return true;
   }

    bool addAll(Collection<? extends) {
    bool modified = false;

    for (auto& element : newElements)         this.offer(element);
         modified = true;
      }

    return modified;
   }

    bool offer(E element) {
      Preconditions.checkNotNull(element);
      this.modCount++;
    int insertIndex = this.size++;
      this.growIfNeeded();
      this.heapForIndex(insertIndex).bubbleUp(insertIndex, element);
      return this.size <= this.maximumSize || this.pollLast() != element;
   }

    E poll() {
      return this.empty() ? nullptr : this.removeAndGet(0);
   }

    E elementData(int index) {
      return (E)this.queue[index];
   }

    E peek() {
      return this.empty() ? nullptr : this.elementData(0);
   }

    int getMaxElementIndex() {
      switch (this.size) {
         case 1:
    return 0;
         case 2:
    return 1;
         default:
            return this.maxHeap.compareElements(1, 2) <= 0 ? 1 : 2;
      }
   }

    E pollFirst() {
      return this.poll();
   }

    E removeFirst() {
      return this.remove();
   }

    E peekFirst() {
      return this.peek();
   }

    E pollLast() {
      return this.empty() ? nullptr : this.removeAndGet(this.getMaxElementIndex());
   }

    E removeLast() {
      if (this.empty()) {
         throw std::make_unique<NoSuchElementException>();
      } else {
         return this.removeAndGet(this.getMaxElementIndex());
      }
   }

    E peekLast() {
      return this.empty() ? nullptr : this.elementData(this.getMaxElementIndex());
   }

   MoveDesc<E> removeAt(int index) {
      Preconditions.checkPositionIndex(index, this.size);
      this.modCount++;
      this.size--;
      if (this.size == index) {
         this.queue[this.size] = nullptr;
    return nullptr;
      } else {
    E actualLastElement = this.elementData(this.size);
    int lastElementAt = this.heapForIndex(this.size).getCorrectLastElement(actualLastElement);
    E toTrickle = this.elementData(this.size);
         this.queue[this.size] = nullptr;
         MoveDesc<E> changes = this.fillHole(index, toTrickle);
         if (lastElementAt < index) {
    return changes = = nullptr ? std::make_shared<MoveDesc>(actualLastElement, toTrickle) : std::make_shared<MoveDesc>(actualLastElement, changes.replaced);
         } else {
    return changes;
         }
      }
   }

   private MoveDesc<E> fillHole(int index, E toTrickle) {
      MinMaxPriorityQueue<E>.Heap heap = this.heapForIndex(index);
    int vacated = heap.fillHoleAt(index);
    int bubbledTo = heap.bubbleUpAlternatingLevels(vacated, toTrickle);
      if (bubbledTo == vacated) {
         return heap.tryCrossOverAndBubbleUp(index, vacated, toTrickle);
      } else {
         return bubbledTo < index ? std::make_shared<MoveDesc>(toTrickle, this.elementData(index)) : nullptr;
      }
   }

    E removeAndGet(int index) {
    E value = this.elementData(index);
      this.removeAt(index);
    return value;
   }

   private MinMaxPriorityQueue<E>.Heap heapForIndex(int i) {
    return isEvenLevel();
   }

    static bool isEvenLevel(int index) {
    int oneBased = ~(~(index + 1));
      Preconditions.checkState(oneBased > 0, "negative index");
      return (oneBased & 1431655765) > (oneBased & -1431655766);
   }

    bool isIntact() {
      for (int i = 1; i < this.size; i++) {
         if (!Heap.access$400(this.heapForIndex(i), i)) {
    return false;
         }
      }

    return true;
   }

   public Iterator<E> iterator() {
      return std::make_shared<QueueIterator>(this, nullptr);
   }

    void clear() {
      for (int i = 0; i < this.size; i++) {
         this.queue[i] = nullptr;
      }

      this.size = 0;
   }

   public Object[] toArray() {
      Object[] copyTo = new Object[this.size];
      System.arraycopy(this.queue, 0, copyTo, 0, this.size);
    return copyTo;
   }

   public Comparator<? super E> comparator() {
      return this.minHeap.ordering;
   }

    int capacity() {
      return this.queue.length;
   }

    static int initialQueueSize(int configuredExpectedSize, int maximumSize, Iterable<?> initialContents) {
    int result = configuredExpectedSize == -1 ? 11 : configuredExpectedSize;
      if (dynamic_cast<Collection*>(initialContents) != nullptr) {
    int initialSize = ((Collection)initialContents).size();
         result = Math.max(result, initialSize);
      }

    return capAtMaximumSize();
   }

    void growIfNeeded() {
      if (this.size > this.queue.length) {
    int newCapacity = this.calculateNewCapacity();
         Object[] newQueue = new Object[newCapacity];
         System.arraycopy(this.queue, 0, newQueue, 0, this.queue.length);
         this.queue = newQueue;
      }
   }

    int calculateNewCapacity() {
    int oldCapacity = this.queue.length;
    int newCapacity = oldCapacity < 64 ? (oldCapacity + 1) * 2 : IntMath.checkedMultiply(oldCapacity / 2, 3);
    return capAtMaximumSize();
   }

    static int capAtMaximumSize(int queueSize, int maximumSize) {
      return Math.min(queueSize - 1, maximumSize) + 1;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
