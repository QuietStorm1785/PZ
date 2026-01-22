#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TByteCollection.h"
#include "gnu/trove/iterator/TByteIterator.h"
#include "gnu/trove/procedure/TByteProcedure.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace impl {
namespace sync {


class TSynchronizedByteCollection {
public:
    static const long serialVersionUID = 3053995032091335093L;
    const TByteCollection c;
    const void* mutex;

    public TSynchronizedByteCollection(TByteCollection c) {
      if (c == nullptr) {
         throw std::make_unique<NullPointerException>();
      } else {
         this.c = c;
         this.mutex = this;
      }
   }

    public TSynchronizedByteCollection(TByteCollection c, void* mutex) {
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

    bool contains(uint8_t o) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.contains(o);
      }
   }

   public byte[] toArray() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.toArray();
      }
   }

   public byte[] toArray(byte[] a) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.toArray(a);
      }
   }

    TByteIterator iterator() {
      return this.c.iterator();
   }

    bool add(uint8_t e) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.push_back(e);
      }
   }

    bool remove(uint8_t o) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.remove(o);
      }
   }

    bool containsAll(Collection<?> coll) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.containsAll(coll);
      }
   }

    bool containsAll(TByteCollection coll) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.containsAll(coll);
      }
   }

    bool containsAll(byte[] array) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.containsAll(array);
      }
   }

    bool addAll(Collection<? extends) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.addAll(coll);
      }
   }

    bool addAll(TByteCollection coll) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.addAll(coll);
      }
   }

    bool addAll(byte[] array) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.addAll(array);
      }
   }

    bool removeAll(Collection<?> coll) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.removeAll(coll);
      }
   }

    bool removeAll(TByteCollection coll) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.removeAll(coll);
      }
   }

    bool removeAll(byte[] array) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.removeAll(array);
      }
   }

    bool retainAll(Collection<?> coll) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.retainAll(coll);
      }
   }

    bool retainAll(TByteCollection coll) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.retainAll(coll);
      }
   }

    bool retainAll(byte[] array) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.retainAll(array);
      }
   }

    uint8_t getNoEntryValue() {
      return this.c.getNoEntryValue();
   }

    bool forEach(TByteProcedure procedure) {
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
