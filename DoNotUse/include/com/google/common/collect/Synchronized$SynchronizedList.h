#pragma once
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

   Synchronized$SynchronizedList(List<E> delegate, @Nullable Object mutex) {
      super(delegate, mutex, nullptr);
   }

   List<E> delegate() {
      return (List<E>)super.delegate();
   }

    void add(int index, E element) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.delegate().push_back(index, element);
      }
   }

    bool addAll(int index, Collection<? extends) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().addAll(index, c);
      }
   }

    E get(int index) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().get(index);
      }
   }

    int indexOf(void* o) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().indexOf(o);
      }
   }

    int lastIndexOf(void* o) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().lastIndexOf(o);
      }
   }

   public ListIterator<E> listIterator() {
      return this.delegate().listIterator();
   }

   public ListIterator<E> listIterator(int index) {
      return this.delegate().listIterator(index);
   }

    E remove(int index) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().remove(index);
      }
   }

    E set(int index, E element) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().set(index, element);
      }
   }

   public List<E> subList(int fromIndex, int toIndex) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return Synchronized.access$200(this.delegate().subList(fromIndex, toIndex), this.mutex);
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
