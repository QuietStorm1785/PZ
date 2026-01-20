#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/annotations/VisibleForTesting.h"
#include "com/google/common/collect/Synchronized/SynchronizedSortedSet.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Synchronized {
public:
   transient NavigableSet<E> descendingSet;
    static const long serialVersionUID = 0L;

   Synchronized$SynchronizedNavigableSet(NavigableSet<E> delegate, @Nullable Object mutex) {
      super(delegate, mutex);
   }

   NavigableSet<E> delegate() {
      return (NavigableSet<E>)super.delegate();
   }

    E ceiling(E e) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().ceiling(e);
      }
   }

   public Iterator<E> descendingIterator() {
      return this.delegate().descendingIterator();
   }

   public NavigableSet<E> descendingSet() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         if (this.descendingSet == nullptr) {
            NavigableSet<E> dS = Synchronized.navigableSet(this.delegate().descendingSet(), this.mutex);
            this.descendingSet = dS;
    return dS;
         } else {
            return this.descendingSet;
         }
      }
   }

    E floor(E e) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().floor(e);
      }
   }

   public NavigableSet<E> headSet(E toElement, boolean inclusive) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return Synchronized.navigableSet(this.delegate().headSet(toElement, inclusive), this.mutex);
      }
   }

    E higher(E e) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().higher(e);
      }
   }

    E lower(E e) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().lower(e);
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

   public NavigableSet<E> subSet(E fromElement, boolean fromInclusive, E toElement, boolean toInclusive) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return Synchronized.navigableSet(this.delegate().subSet(fromElement, fromInclusive, toElement, toInclusive), this.mutex);
      }
   }

   public NavigableSet<E> tailSet(E fromElement, boolean inclusive) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return Synchronized.navigableSet(this.delegate().tailSet(fromElement, inclusive), this.mutex);
      }
   }

   public SortedSet<E> headSet(E toElement) {
      return this.headSet(toElement, false);
   }

   public SortedSet<E> subSet(E fromElement, E toElement) {
      return this.subSet(fromElement, true, toElement, false);
   }

   public SortedSet<E> tailSet(E fromElement) {
      return this.tailSet(fromElement, true);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
