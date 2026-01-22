#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TShortCollection.h"
#include "gnu/trove/function/TShortFunction.h"
#include "gnu/trove/iterator/TByteShortIterator.h"
#include "gnu/trove/map/TByteShortMap.h"
#include "gnu/trove/procedure/TByteProcedure.h"
#include "gnu/trove/procedure/TByteShortProcedure.h"
#include "gnu/trove/procedure/TShortProcedure.h"
#include "gnu/trove/set/TByteSet.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace impl {
namespace sync {


class TSynchronizedByteShortMap {
public:
    static const long serialVersionUID = 1978198479659022715L;
    const TByteShortMap m;
    const void* mutex;
   private transient TByteSet keySet = nullptr;
   private transient TShortCollection values = nullptr;

    public TSynchronizedByteShortMap(TByteShortMap m) {
      if (m == nullptr) {
         throw std::make_unique<NullPointerException>();
      } else {
         this.m = m;
         this.mutex = this;
      }
   }

    public TSynchronizedByteShortMap(TByteShortMap m, void* mutex) {
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

    bool containsKey(uint8_t key) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.containsKey(key);
      }
   }

    bool containsValue(short value) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.containsValue(value);
      }
   }

    short get(uint8_t key) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.get(key);
      }
   }

    short put(uint8_t key, short value) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.put(key, value);
      }
   }

    short remove(uint8_t key) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.remove(key);
      }
   }

    void putAll(Map<? extends, ? extends) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.m.putAll(map);
      }
   }

    void putAll(TByteShortMap map) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.m.putAll(map);
      }
   }

    void clear() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.m.clear();
      }
   }

    TByteSet keySet() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         if (this.keySet == nullptr) {
            this.keySet = std::make_shared<TSynchronizedByteSet>(this.m.keySet(), this.mutex);
         }

         return this.keySet;
      }
   }

   public byte[] keys() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.keys();
      }
   }

   public byte[] keys(byte[] array) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.keys(array);
      }
   }

    TShortCollection valueCollection() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         if (this.values == nullptr) {
            this.values = std::make_shared<TSynchronizedShortCollection>(this.m.valueCollection(), this.mutex);
         }

         return this.values;
      }
   }

   public short[] values() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.values();
      }
   }

   public short[] values(short[] array) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.values(array);
      }
   }

    TByteShortIterator iterator() {
      return this.m.iterator();
   }

    uint8_t getNoEntryKey() {
      return this.m.getNoEntryKey();
   }

    short getNoEntryValue() {
      return this.m.getNoEntryValue();
   }

    short putIfAbsent(uint8_t key, short value) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.putIfAbsent(key, value);
      }
   }

    bool forEachKey(TByteProcedure procedure) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.forEachKey(procedure);
      }
   }

    bool forEachValue(TShortProcedure procedure) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.forEachValue(procedure);
      }
   }

    bool forEachEntry(TByteShortProcedure procedure) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.forEachEntry(procedure);
      }
   }

    void transformValues(TShortFunction function) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.m.transformValues(function);
      }
   }

    bool retainEntries(TByteShortProcedure procedure) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.retainEntries(procedure);
      }
   }

    bool increment(uint8_t key) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.increment(key);
      }
   }

    bool adjustValue(uint8_t key, short amount) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.adjustValue(key, amount);
      }
   }

    short adjustOrPutValue(uint8_t key, short adjust_amount, short put_amount) {
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
