#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Synchronized/SynchronizedSet.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Synchronized {
public:
    static const long serialVersionUID = 0L;

   Synchronized$SynchronizedSortedSet(SortedSet<E> delegate, @Nullable Object mutex) {
      super(delegate, mutex);
   }

   SortedSet<E> delegate() {
      return (SortedSet<E>)super.delegate();
   }

   public Comparator<? super E> comparator() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().comparator();
      }
   }

   public SortedSet<E> subSet(E fromElement, E toElement) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return Synchronized.access$100(this.delegate().subSet(fromElement, toElement), this.mutex);
      }
   }

   public SortedSet<E> headSet(E toElement) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return Synchronized.access$100(this.delegate().headSet(toElement), this.mutex);
      }
   }

   public SortedSet<E> tailSet(E fromElement) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return Synchronized.access$100(this.delegate().tailSet(fromElement), this.mutex);
      }
   }

    E first() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().first();
      }
   }

    E last() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().last();
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
