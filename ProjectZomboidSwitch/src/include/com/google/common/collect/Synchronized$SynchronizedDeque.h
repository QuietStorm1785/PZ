#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Synchronized/SynchronizedQueue.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Synchronized {
public:
    static const long serialVersionUID = 0L;

   Synchronized$SynchronizedDeque(std::deque<E> delegate, @Nullable Object mutex) {
      super(delegate, mutex);
   }

   std::deque<E> delegate() {
      return (std::deque<E>)super.delegate();
   }

    void addFirst(E e) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.delegate().addFirst(e);
      }
   }

    void addLast(E e) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.delegate().addLast(e);
      }
   }

    bool offerFirst(E e) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().offerFirst(e);
      }
   }

    bool offerLast(E e) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().offerLast(e);
      }
   }

    E removeFirst() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().removeFirst();
      }
   }

    E removeLast() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().removeLast();
      }
   }

    E pollFirst() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().pollFirst();
      }
   }

    E pollLast() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().pollLast();
      }
   }

    E getFirst() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().getFirst();
      }
   }

    E getLast() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().getLast();
      }
   }

    E peekFirst() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().peekFirst();
      }
   }

    E peekLast() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().peekLast();
      }
   }

    bool removeFirstOccurrence(void* o) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().removeFirstOccurrence(o);
      }
   }

    bool removeLastOccurrence(void* o) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().removeLastOccurrence(o);
      }
   }

    void push(E e) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.delegate().push(e);
      }
   }

    E pop() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().pop();
      }
   }

   public Iterator<E> descendingIterator() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().descendingIterator();
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
