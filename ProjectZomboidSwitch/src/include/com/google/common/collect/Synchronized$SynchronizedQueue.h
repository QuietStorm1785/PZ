#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Synchronized/SynchronizedCollection.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Synchronized {
public:
    static const long serialVersionUID = 0L;

   Synchronized$SynchronizedQueue(std::queue<E> delegate, @Nullable Object mutex) {
      super(delegate, mutex, nullptr);
   }

   std::queue<E> delegate() {
      return (std::queue<E>)super.delegate();
   }

    E element() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().element();
      }
   }

    bool offer(E e) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().offer(e);
      }
   }

    E peek() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().peek();
      }
   }

    E poll() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().poll();
      }
   }

    E remove() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().remove();
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
