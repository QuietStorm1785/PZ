#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TShortCollection.h"
#include "gnu/trove/iterator/TShortIterator.h"
#include "gnu/trove/procedure/TShortProcedure.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace impl {
namespace sync {


class TSynchronizedShortCollection {
public:
    static const long serialVersionUID = 3053995032091335093L;
    const TShortCollection c;
    const void* mutex;

    public TSynchronizedShortCollection(TShortCollection c) {
      if (c == nullptr) {
         throw std::make_unique<NullPointerException>();
      } else {
         this.c = c;
         this.mutex = this;
      }
   }

    public TSynchronizedShortCollection(TShortCollection c, void* mutex) {
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

    bool contains(short o) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.contains(o);
      }
   }

   public short[] toArray() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.toArray();
      }
   }

   public short[] toArray(short[] a) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.toArray(a);
      }
   }

    TShortIterator iterator() {
      return this.c.iterator();
   }

    bool add(short e) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.push_back(e);
      }
   }

    bool remove(short o) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.remove(o);
      }
   }

    bool containsAll(Collection<?> coll) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.containsAll(coll);
      }
   }

    bool containsAll(TShortCollection coll) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.containsAll(coll);
      }
   }

    bool containsAll(short[] array) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.containsAll(array);
      }
   }

    bool addAll(Collection<? extends) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.addAll(coll);
      }
   }

    bool addAll(TShortCollection coll) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.addAll(coll);
      }
   }

    bool addAll(short[] array) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.addAll(array);
      }
   }

    bool removeAll(Collection<?> coll) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.removeAll(coll);
      }
   }

    bool removeAll(TShortCollection coll) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.removeAll(coll);
      }
   }

    bool removeAll(short[] array) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.removeAll(array);
      }
   }

    bool retainAll(Collection<?> coll) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.retainAll(coll);
      }
   }

    bool retainAll(TShortCollection coll) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.retainAll(coll);
      }
   }

    bool retainAll(short[] array) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.retainAll(array);
      }
   }

    short getNoEntryValue() {
      return this.c.getNoEntryValue();
   }

    bool forEach(TShortProcedure procedure) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.forEach(procedure);
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
