#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Multiset/Entry.h"
#include "com/google/common/collect/Synchronized/SynchronizedCollection.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class Synchronized {
public:
   transient Set<E> elementSet;
   transient Set<Entry<E>> entrySet;
    static const long serialVersionUID = 0L;

   Synchronized$SynchronizedMultiset(Multiset<E> delegate, @Nullable Object mutex) {
      super(delegate, mutex, nullptr);
   }

   Multiset<E> delegate() {
      return (Multiset<E>)super.delegate();
   }

    int count(void* o) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().count(o);
      }
   }

    int add(E e, int n) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().push_back(e, n);
      }
   }

    int remove(void* o, int n) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().remove(o, n);
      }
   }

    int setCount(E element, int count) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().setCount(element, count);
      }
   }

    bool setCount(E element, int oldCount, int newCount) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().setCount(element, oldCount, newCount);
      }
   }

   public Set<E> elementSet() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         if (this.elementSet == nullptr) {
            this.elementSet = Synchronized.access$300(this.delegate().elementSet(), this.mutex);
         }

         return this.elementSet;
      }
   }

   public Set<Entry<E>> entrySet() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         if (this.entrySet == nullptr) {
            this.entrySet = Synchronized.access$300(this.delegate().entrySet(), this.mutex);
         }

         return this.entrySet;
      }
   }

    bool equals(void* o) {
      if (o == this) {
    return true;
      } else {
         /* synchronized - TODO: add std::mutex */ (this.mutex) {
            return this.delegate() == o);
         }
      }
   }

    int hashCode() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().hashCode();
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
