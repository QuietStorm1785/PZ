#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TFloatCollection.h"
#include "gnu/trove/function/TFloatFunction.h"
#include "gnu/trove/iterator/TCharFloatIterator.h"
#include "gnu/trove/map/TCharFloatMap.h"
#include "gnu/trove/procedure/TCharFloatProcedure.h"
#include "gnu/trove/procedure/TCharProcedure.h"
#include "gnu/trove/procedure/TFloatProcedure.h"
#include "gnu/trove/set/TCharSet.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace impl {
namespace sync {


class TSynchronizedCharFloatMap {
public:
    static const long serialVersionUID = 1978198479659022715L;
    const TCharFloatMap m;
    const void* mutex;
   private transient TCharSet keySet = nullptr;
   private transient TFloatCollection values = nullptr;

    public TSynchronizedCharFloatMap(TCharFloatMap m) {
      if (m == nullptr) {
         throw std::make_unique<NullPointerException>();
      } else {
         this.m = m;
         this.mutex = this;
      }
   }

    public TSynchronizedCharFloatMap(TCharFloatMap m, void* mutex) {
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

    bool containsKey(char key) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.containsKey(key);
      }
   }

    bool containsValue(float value) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.containsValue(value);
      }
   }

    float get(char key) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.get(key);
      }
   }

    float put(char key, float value) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.put(key, value);
      }
   }

    float remove(char key) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.remove(key);
      }
   }

    void putAll(Map<? extends, ? extends) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.m.putAll(map);
      }
   }

    void putAll(TCharFloatMap map) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.m.putAll(map);
      }
   }

    void clear() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.m.clear();
      }
   }

    TCharSet keySet() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         if (this.keySet == nullptr) {
            this.keySet = std::make_shared<TSynchronizedCharSet>(this.m.keySet(), this.mutex);
         }

         return this.keySet;
      }
   }

   public char[] keys() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.keys();
      }
   }

   public char[] keys(char[] array) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.keys(array);
      }
   }

    TFloatCollection valueCollection() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         if (this.values == nullptr) {
            this.values = std::make_shared<TSynchronizedFloatCollection>(this.m.valueCollection(), this.mutex);
         }

         return this.values;
      }
   }

   public float[] values() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.values();
      }
   }

   public float[] values(float[] array) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.values(array);
      }
   }

    TCharFloatIterator iterator() {
      return this.m.iterator();
   }

    char getNoEntryKey() {
      return this.m.getNoEntryKey();
   }

    float getNoEntryValue() {
      return this.m.getNoEntryValue();
   }

    float putIfAbsent(char key, float value) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.putIfAbsent(key, value);
      }
   }

    bool forEachKey(TCharProcedure procedure) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.forEachKey(procedure);
      }
   }

    bool forEachValue(TFloatProcedure procedure) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.forEachValue(procedure);
      }
   }

    bool forEachEntry(TCharFloatProcedure procedure) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.forEachEntry(procedure);
      }
   }

    void transformValues(TFloatFunction function) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.m.transformValues(function);
      }
   }

    bool retainEntries(TCharFloatProcedure procedure) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.retainEntries(procedure);
      }
   }

    bool increment(char key) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.increment(key);
      }
   }

    bool adjustValue(char key, float amount) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.adjustValue(key, amount);
      }
   }

    float adjustOrPutValue(char key, float adjust_amount, float put_amount) {
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
