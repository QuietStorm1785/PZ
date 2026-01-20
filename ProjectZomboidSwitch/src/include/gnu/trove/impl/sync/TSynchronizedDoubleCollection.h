#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TDoubleCollection.h"
#include "gnu/trove/iterator/TDoubleIterator.h"
#include "gnu/trove/procedure/TDoubleProcedure.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace impl {
namespace sync {


class TSynchronizedDoubleCollection {
public:
    static const long serialVersionUID = 3053995032091335093L;
    const TDoubleCollection c;
    const void* mutex;

    public TSynchronizedDoubleCollection(TDoubleCollection c) {
      if (c == nullptr) {
         throw std::make_unique<NullPointerException>();
      } else {
         this.c = c;
         this.mutex = this;
      }
   }

    public TSynchronizedDoubleCollection(TDoubleCollection c, void* mutex) {
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

    bool contains(double o) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.contains(o);
      }
   }

   public double[] toArray() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.toArray();
      }
   }

   public double[] toArray(double[] a) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.toArray(a);
      }
   }

    TDoubleIterator iterator() {
      return this.c.iterator();
   }

    bool add(double e) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.push_back(e);
      }
   }

    bool remove(double o) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.remove(o);
      }
   }

    bool containsAll(Collection<?> coll) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.containsAll(coll);
      }
   }

    bool containsAll(TDoubleCollection coll) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.containsAll(coll);
      }
   }

    bool containsAll(double[] array) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.containsAll(array);
      }
   }

    bool addAll(Collection<? extends) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.addAll(coll);
      }
   }

    bool addAll(TDoubleCollection coll) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.addAll(coll);
      }
   }

    bool addAll(double[] array) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.addAll(array);
      }
   }

    bool removeAll(Collection<?> coll) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.removeAll(coll);
      }
   }

    bool removeAll(TDoubleCollection coll) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.removeAll(coll);
      }
   }

    bool removeAll(double[] array) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.removeAll(array);
      }
   }

    bool retainAll(Collection<?> coll) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.retainAll(coll);
      }
   }

    bool retainAll(TDoubleCollection coll) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.retainAll(coll);
      }
   }

    bool retainAll(double[] array) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.retainAll(array);
      }
   }

    double getNoEntryValue() {
      return this.c.getNoEntryValue();
   }

    bool forEach(TDoubleProcedure procedure) {
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
