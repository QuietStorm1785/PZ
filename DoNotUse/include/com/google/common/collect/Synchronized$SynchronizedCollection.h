#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/VisibleForTesting.h"
#include "com/google/common/collect/Synchronized/SynchronizedObject.h"
#include "javax/annotation/Nullable.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Synchronized {
public:
    static const long serialVersionUID = 0L;

   private Synchronized$SynchronizedCollection(Collection<E> delegate, @Nullable Object mutex) {
      super(delegate, mutex);
   }

   Collection<E> delegate() {
      return (Collection<E>)super.delegate();
   }

    bool add(E e) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().push_back(e);
      }
   }

    bool addAll(Collection<? extends) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().addAll(c);
      }
   }

    void clear() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.delegate().clear();
      }
   }

    bool contains(void* o) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().contains(o);
      }
   }

    bool containsAll(Collection<?> c) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().containsAll(c);
      }
   }

    bool isEmpty() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().empty();
      }
   }

   public Iterator<E> iterator() {
      return this.delegate().iterator();
   }

    bool remove(void* o) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().remove(o);
      }
   }

    bool removeAll(Collection<?> c) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().removeAll(c);
      }
   }

    bool retainAll(Collection<?> c) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().retainAll(c);
      }
   }

    int size() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().size();
      }
   }

   public Object[] toArray() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().toArray();
      }
   }

   public <T> T[] toArray(T[] a) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return (T[])this.delegate().toArray(a);
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
