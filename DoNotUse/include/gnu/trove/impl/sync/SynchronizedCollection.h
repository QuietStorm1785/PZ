#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <iterator>

namespace gnu {
namespace trove {
namespace impl {
namespace sync {


class SynchronizedCollection {
public:
    static const long serialVersionUID = 3053995032091335093L;
   const Collection<E> c;
    const void* mutex;

   SynchronizedCollection(Collection<E> c, Object mutex) {
      this.c = c;
      this.mutex = mutex;
   }

    int size() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.size();
      }
   }

    bool isEmpty() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.empty();
      }
   }

    bool contains(void* o) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.contains(o);
      }
   }

   public Object[] toArray() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.toArray();
      }
   }

   public <T> T[] toArray(T[] a) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return (T[])this.c.toArray(a);
      }
   }

   public Iterator<E> iterator() {
      return this.c.iterator();
   }

    bool add(E e) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.push_back(e);
      }
   }

    bool remove(void* o) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.remove(o);
      }
   }

    bool containsAll(Collection<?> coll) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.containsAll(coll);
      }
   }

    bool addAll(Collection<? extends) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.addAll(coll);
      }
   }

    bool removeAll(Collection<?> coll) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.removeAll(coll);
      }
   }

    bool retainAll(Collection<?> coll) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.retainAll(coll);
      }
   }

    void clear() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.c.clear();
      }
   }

    std::string toString() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c;
      }
   }

    void writeObject(ObjectOutputStream s) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         s.defaultWriteObject();
      }
   }
}
} // namespace sync
} // namespace impl
} // namespace trove
} // namespace gnu
