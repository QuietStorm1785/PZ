#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TIntCollection.h"
#include "gnu/trove/iterator/TIntIterator.h"
#include "gnu/trove/procedure/TIntProcedure.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace impl {
namespace sync {


class TSynchronizedIntCollection {
public:
    static const long serialVersionUID = 3053995032091335093L;
    const TIntCollection c;
    const void* mutex;

    public TSynchronizedIntCollection(TIntCollection c) {
      if (c == nullptr) {
         throw std::make_unique<NullPointerException>();
      } else {
         this.c = c;
         this.mutex = this;
      }
   }

    public TSynchronizedIntCollection(TIntCollection c, void* mutex) {
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

    bool contains(int o) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.contains(o);
      }
   }

   public int[] toArray() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.toArray();
      }
   }

   public int[] toArray(int[] a) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.toArray(a);
      }
   }

    TIntIterator iterator() {
      return this.c.iterator();
   }

    bool add(int e) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.push_back(e);
      }
   }

    bool remove(int o) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.remove(o);
      }
   }

    bool containsAll(Collection<?> coll) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.containsAll(coll);
      }
   }

    bool containsAll(TIntCollection coll) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.containsAll(coll);
      }
   }

    bool containsAll(int[] array) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.containsAll(array);
      }
   }

    bool addAll(Collection<? extends) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.addAll(coll);
      }
   }

    bool addAll(TIntCollection coll) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.addAll(coll);
      }
   }

    bool addAll(int[] array) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.addAll(array);
      }
   }

    bool removeAll(Collection<?> coll) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.removeAll(coll);
      }
   }

    bool removeAll(TIntCollection coll) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.removeAll(coll);
      }
   }

    bool removeAll(int[] array) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.removeAll(array);
      }
   }

    bool retainAll(Collection<?> coll) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.retainAll(coll);
      }
   }

    bool retainAll(TIntCollection coll) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.retainAll(coll);
      }
   }

    bool retainAll(int[] array) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.retainAll(array);
      }
   }

    int getNoEntryValue() {
      return this.c.getNoEntryValue();
   }

    bool forEach(TIntProcedure procedure) {
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
