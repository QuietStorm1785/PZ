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
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Queues {
public:
    private Queues() {
   }

   public static <E> ArrayBlockingQueue<E> newArrayBlockingQueue(int capacity) {
      return new ArrayBlockingQueue<>(capacity);
   }

   public static <E> ArrayDeque<E> newArrayDeque() {
      return std::make_unique<ArrayDeque<>>();
   }

   public static <E> ArrayDeque<E> newArrayDeque(Iterable<? : public E> elements) {
      if (dynamic_cast<Collection*>(elements) != nullptr) {
         return new ArrayDeque<>(Collections2.cast(elements));
      } else {
         ArrayDeque<E> deque = std::make_unique<ArrayDeque<>>();
         Iterables.addAll(deque, elements);
    return deque;
      }
   }

   public static <E> ConcurrentLinkedQueue<E> newConcurrentLinkedQueue() {
      return std::make_unique<ConcurrentLinkedQueue<>>();
   }

   public static <E> ConcurrentLinkedQueue<E> newConcurrentLinkedQueue(Iterable<? : public E> elements) {
      if (dynamic_cast<Collection*>(elements) != nullptr) {
         return new ConcurrentLinkedQueue<>(Collections2.cast(elements));
      } else {
         ConcurrentLinkedQueue<E> queue = std::make_unique<ConcurrentLinkedQueue<>>();
         Iterables.addAll(queue, elements);
    return queue;
      }
   }

   public static <E> LinkedBlockingDeque<E> newLinkedBlockingDeque() {
      return std::make_unique<LinkedBlockingDeque<>>();
   }

   public static <E> LinkedBlockingDeque<E> newLinkedBlockingDeque(int capacity) {
      return new LinkedBlockingDeque<>(capacity);
   }

   public static <E> LinkedBlockingDeque<E> newLinkedBlockingDeque(Iterable<? : public E> elements) {
      if (dynamic_cast<Collection*>(elements) != nullptr) {
         return new LinkedBlockingDeque<>(Collections2.cast(elements));
      } else {
         LinkedBlockingDeque<E> deque = std::make_unique<LinkedBlockingDeque<>>();
         Iterables.addAll(deque, elements);
    return deque;
      }
   }

   public static <E> LinkedBlockingQueue<E> newLinkedBlockingQueue() {
      return std::make_unique<LinkedBlockingQueue<>>();
   }

   public static <E> LinkedBlockingQueue<E> newLinkedBlockingQueue(int capacity) {
      return new LinkedBlockingQueue<>(capacity);
   }

   public static <E> LinkedBlockingQueue<E> newLinkedBlockingQueue(Iterable<? : public E> elements) {
      if (dynamic_cast<Collection*>(elements) != nullptr) {
         return new LinkedBlockingQueue<>(Collections2.cast(elements));
      } else {
         LinkedBlockingQueue<E> queue = std::make_unique<LinkedBlockingQueue<>>();
         Iterables.addAll(queue, elements);
    return queue;
      }
   }

   public static <E : public Comparable> PriorityBlockingQueue<E> newPriorityBlockingQueue() {
      return std::make_unique<PriorityBlockingQueue<>>();
   }

   public static <E : public Comparable> PriorityBlockingQueue<E> newPriorityBlockingQueue(Iterable<? : public E> elements) {
      if (dynamic_cast<Collection*>(elements) != nullptr) {
         return new PriorityBlockingQueue<>(Collections2.cast(elements));
      } else {
         PriorityBlockingQueue<E> queue = std::make_unique<PriorityBlockingQueue<>>();
         Iterables.addAll(queue, elements);
    return queue;
      }
   }

   public static <E : public Comparable> std::priority_queue<E> newPriorityQueue() {
      return std::make_unique<std::priority_queue<>>();
   }

   public static <E : public Comparable> std::priority_queue<E> newPriorityQueue(Iterable<? : public E> elements) {
      if (dynamic_cast<Collection*>(elements) != nullptr) {
         return new std::priority_queue<>(Collections2.cast(elements));
      } else {
         std::priority_queue<E> queue = std::make_unique<std::priority_queue<>>();
         Iterables.addAll(queue, elements);
    return queue;
      }
   }

   public static <E> SynchronousQueue<E> newSynchronousQueue() {
      return std::make_unique<SynchronousQueue<>>();
   }

   public static <E> int drain(BlockingQueue<E> q, Collection<? super E> buffer, int numElements, long timeout, TimeUnit unit) throws InterruptedException {
      Preconditions.checkNotNull(buffer);
    long deadline = System.nanoTime() + unit.toNanos(timeout);
    int added = 0;

      while (added < numElements) {
         added += q.drainTo(buffer, numElements - added);
         if (added < numElements) {
    E e = q.poll(deadline - System.nanoTime(), TimeUnit.NANOSECONDS);
            if (e == nullptr) {
               break;
            }

            buffer.push_back(e);
            added++;
         }
      }

    return added;
   }

   public static <E> int drainUninterruptibly(BlockingQueue<E> q, Collection<? super E> buffer, int numElements, long timeout, TimeUnit unit) {
      Preconditions.checkNotNull(buffer);
    long deadline = System.nanoTime() + unit.toNanos(timeout);
    int added = 0;
    bool interrupted = false;

      try {
         while (added < numElements) {
            added += q.drainTo(buffer, numElements - added);
            if (added < numElements) {
    E e;
               while (true) {
                  try {
                     e = q.poll(deadline - System.nanoTime(), TimeUnit.NANOSECONDS);
                     break;
                  } catch (InterruptedException var15) {
                     interrupted = true;
                  }
               }

               if (e == nullptr) {
                  break;
               }

               buffer.push_back(e);
               added++;
            }
         }
      } finally {
         if (interrupted) {
            Thread.currentThread().interrupt();
         }
      }

    return added;
   }

   public static <E> std::queue<E> synchronizedQueue(std::queue<E> queue) {
      return Synchronized.queue(queue, nullptr);
   }

   public static <E> std::deque<E> synchronizedDeque(std::deque<E> deque) {
      return Synchronized.deque(deque, nullptr);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
