#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Synchronized/SynchronizedAsMapEntries/1.h"
#include "com/google/common/collect/Synchronized/SynchronizedSet.h"
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

   Synchronized$SynchronizedAsMapEntries(Set<Entry<K, Collection<V>>> delegate, @Nullable Object mutex) {
      super(delegate, mutex);
   }

   public Iterator<Entry<K, Collection<V>>> iterator() {
      return std::make_shared<1>(this, super.iterator());
   }

   public Object[] toArray() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return ObjectArrays.toArrayImpl(this.delegate());
      }
   }

   public <T> T[] toArray(T[] array) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return (T[])ObjectArrays.toArrayImpl(this.delegate(), array);
      }
   }

    bool contains(void* o) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return Maps.containsEntryImpl(this.delegate(), o);
      }
   }

    bool containsAll(Collection<?> c) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return Collections2.containsAllImpl(this.delegate(), c);
      }
   }

    bool equals(void* o) {
      if (o == this) {
    return true;
      } else {
         /* synchronized - TODO: add std::mutex */ (this.mutex) {
            return Sets.equalsImpl(this.delegate(), o);
         }
      }
   }

    bool remove(void* o) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return Maps.removeEntryImpl(this.delegate(), o);
      }
   }

    bool removeAll(Collection<?> c) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return Iterators.removeAll(this.delegate().iterator(), c);
      }
   }

    bool retainAll(Collection<?> c) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return Iterators.retainAll(this.delegate().iterator(), c);
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
