#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TByteCollection.h"
#include "gnu/trove/function/TByteFunction.h"
#include "gnu/trove/iterator/TObjectByteIterator.h"
#include "gnu/trove/map/TObjectByteMap.h"
#include "gnu/trove/procedure/TByteProcedure.h"
#include "gnu/trove/procedure/TObjectByteProcedure.h"
#include "gnu/trove/procedure/TObjectProcedure.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace impl {
namespace sync {


class TSynchronizedObjectByteMap {
public:
    static const long serialVersionUID = 1978198479659022715L;
   private const TObjectByteMap<K> m;
    const void* mutex;
   private transient Set<K> keySet = nullptr;
   private transient TByteCollection values = nullptr;

    public TSynchronizedObjectByteMap(TObjectByteMap<K> m) {
      if (m == nullptr) {
         throw std::make_unique<NullPointerException>();
      } else {
         this.m = m;
         this.mutex = this;
      }
   }

    public TSynchronizedObjectByteMap(TObjectByteMap<K> m, void* mutex) {
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

    bool containsKey(void* key) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.containsKey(key);
      }
   }

    bool containsValue(uint8_t value) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.containsValue(value);
      }
   }

    uint8_t get(void* key) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.get(key);
      }
   }

    uint8_t put(K key, uint8_t value) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.put(key, value);
      }
   }

    uint8_t remove(void* key) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.remove(key);
      }
   }

    void putAll(Map<? extends, ? extends) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.m.putAll(map);
      }
   }

    void putAll(TObjectByteMap<? extends) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.m.putAll(map);
      }
   }

    void clear() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.m.clear();
      }
   }

   public Set<K> keySet() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         if (this.keySet == nullptr) {
            this.keySet = std::make_shared<SynchronizedSet>(this.m.keySet(), this.mutex);
         }

         return this.keySet;
      }
   }

   public Object[] keys() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.keys();
      }
   }

   public K[] keys(K[] array) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return (K[])this.m.keys(array);
      }
   }

    TByteCollection valueCollection() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         if (this.values == nullptr) {
            this.values = std::make_shared<TSynchronizedByteCollection>(this.m.valueCollection(), this.mutex);
         }

         return this.values;
      }
   }

   public byte[] values() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.values();
      }
   }

   public byte[] values(byte[] array) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.values(array);
      }
   }

   public TObjectByteIterator<K> iterator() {
      return this.m.iterator();
   }

    uint8_t getNoEntryValue() {
      return this.m.getNoEntryValue();
   }

    uint8_t putIfAbsent(K key, uint8_t value) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.putIfAbsent(key, value);
      }
   }

    bool forEachKey(TObjectProcedure<? super) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.forEachKey(procedure);
      }
   }

    bool forEachValue(TByteProcedure procedure) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.forEachValue(procedure);
      }
   }

    bool forEachEntry(TObjectByteProcedure<? super) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.forEachEntry(procedure);
      }
   }

    void transformValues(TByteFunction function) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.m.transformValues(function);
      }
   }

    bool retainEntries(TObjectByteProcedure<? super) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.retainEntries(procedure);
      }
   }

    bool increment(K key) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.increment(key);
      }
   }

    bool adjustValue(K key, uint8_t amount) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.adjustValue(key, amount);
      }
   }

    uint8_t adjustOrPutValue(K key, uint8_t adjust_amount, uint8_t put_amount) {
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
