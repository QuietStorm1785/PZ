#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TDoubleCollection.h"
#include "gnu/trove/function/TDoubleFunction.h"
#include "gnu/trove/iterator/TDoubleDoubleIterator.h"
#include "gnu/trove/map/TDoubleDoubleMap.h"
#include "gnu/trove/procedure/TDoubleDoubleProcedure.h"
#include "gnu/trove/procedure/TDoubleProcedure.h"
#include "gnu/trove/set/TDoubleSet.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace impl {
namespace sync {


class TSynchronizedDoubleDoubleMap {
public:
    static const long serialVersionUID = 1978198479659022715L;
    const TDoubleDoubleMap m;
    const void* mutex;
   private transient TDoubleSet keySet = nullptr;
   private transient TDoubleCollection values = nullptr;

    public TSynchronizedDoubleDoubleMap(TDoubleDoubleMap m) {
      if (m == nullptr) {
         throw std::make_unique<NullPointerException>();
      } else {
         this.m = m;
         this.mutex = this;
      }
   }

    public TSynchronizedDoubleDoubleMap(TDoubleDoubleMap m, void* mutex) {
      this.m = m;
      this.mutex = mutex;
   }

    int size() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.size();
      }
   }

    bool isEmpty() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.empty();
      }
   }

    bool containsKey(double key) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.containsKey(key);
      }
   }

    bool containsValue(double value) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.containsValue(value);
      }
   }

    double get(double key) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.get(key);
      }
   }

    double put(double key, double value) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.put(key, value);
      }
   }

    double remove(double key) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.remove(key);
      }
   }

    void putAll(Map<? extends, ? extends) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.m.putAll(map);
      }
   }

    void putAll(TDoubleDoubleMap map) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.m.putAll(map);
      }
   }

    void clear() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.m.clear();
      }
   }

    TDoubleSet keySet() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         if (this.keySet == nullptr) {
            this.keySet = std::make_shared<TSynchronizedDoubleSet>(this.m.keySet(), this.mutex);
         }

         return this.keySet;
      }
   }

   public double[] keys() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.keys();
      }
   }

   public double[] keys(double[] array) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.keys(array);
      }
   }

    TDoubleCollection valueCollection() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         if (this.values == nullptr) {
            this.values = std::make_shared<TSynchronizedDoubleCollection>(this.m.valueCollection(), this.mutex);
         }

         return this.values;
      }
   }

   public double[] values() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.values();
      }
   }

   public double[] values(double[] array) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.values(array);
      }
   }

    TDoubleDoubleIterator iterator() {
      return this.m.iterator();
   }

    double getNoEntryKey() {
      return this.m.getNoEntryKey();
   }

    double getNoEntryValue() {
      return this.m.getNoEntryValue();
   }

    double putIfAbsent(double key, double value) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.putIfAbsent(key, value);
      }
   }

    bool forEachKey(TDoubleProcedure procedure) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.forEachKey(procedure);
      }
   }

    bool forEachValue(TDoubleProcedure procedure) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.forEachValue(procedure);
      }
   }

    bool forEachEntry(TDoubleDoubleProcedure procedure) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.forEachEntry(procedure);
      }
   }

    void transformValues(TDoubleFunction function) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.m.transformValues(function);
      }
   }

    bool retainEntries(TDoubleDoubleProcedure procedure) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.retainEntries(procedure);
      }
   }

    bool increment(double key) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.increment(key);
      }
   }

    bool adjustValue(double key, double amount) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.adjustValue(key, amount);
      }
   }

    double adjustOrPutValue(double key, double adjust_amount, double put_amount) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.adjustOrPutValue(key, adjust_amount, put_amount);
      }
   }

    bool equals(void* o) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m == o);
      }
   }

    int hashCode() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.hashCode();
      }
   }

    std::string toString() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m;
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
