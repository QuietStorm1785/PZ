#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TLongCollection.h"
#include "gnu/trove/function/TLongFunction.h"
#include "gnu/trove/iterator/TObjectLongIterator.h"
#include "gnu/trove/map/TObjectLongMap.h"
#include "gnu/trove/procedure/TLongProcedure.h"
#include "gnu/trove/procedure/TObjectLongProcedure.h"
#include "gnu/trove/procedure/TObjectProcedure.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace impl {
namespace sync {


class TSynchronizedObjectLongMap {
public:
    static const long serialVersionUID = 1978198479659022715L;
   private const TObjectLongMap<K> m;
    const void* mutex;
   private transient Set<K> keySet = nullptr;
   private transient TLongCollection values = nullptr;

    public TSynchronizedObjectLongMap(TObjectLongMap<K> m) {
      if (m == nullptr) {
         throw std::make_unique<NullPointerException>();
      } else {
         this.m = m;
         this.mutex = this;
      }
   }

    public TSynchronizedObjectLongMap(TObjectLongMap<K> m, void* mutex) {
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

    bool containsValue(long value) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.containsValue(value);
      }
   }

    long get(void* key) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.get(key);
      }
   }

    long put(K key, long value) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.put(key, value);
      }
   }

    long remove(void* key) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.remove(key);
      }
   }

    void putAll(Map<? extends, ? extends) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.m.putAll(map);
      }
   }

    void putAll(TObjectLongMap<? extends) {
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

    TLongCollection valueCollection() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         if (this.values == nullptr) {
            this.values = std::make_shared<TSynchronizedLongCollection>(this.m.valueCollection(), this.mutex);
         }

         return this.values;
      }
   }

   public long[] values() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.values();
      }
   }

   public long[] values(long[] array) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.values(array);
      }
   }

   public TObjectLongIterator<K> iterator() {
      return this.m.iterator();
   }

    long getNoEntryValue() {
      return this.m.getNoEntryValue();
   }

    long putIfAbsent(K key, long value) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.putIfAbsent(key, value);
      }
   }

    bool forEachKey(TObjectProcedure<? super) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.forEachKey(procedure);
      }
   }

    bool forEachValue(TLongProcedure procedure) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.forEachValue(procedure);
      }
   }

    bool forEachEntry(TObjectLongProcedure<? super) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.forEachEntry(procedure);
      }
   }

    void transformValues(TLongFunction function) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.m.transformValues(function);
      }
   }

    bool retainEntries(TObjectLongProcedure<? super) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.retainEntries(procedure);
      }
   }

    bool increment(K key) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.increment(key);
      }
   }

    bool adjustValue(K key, long amount) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.adjustValue(key, amount);
      }
   }

    long adjustOrPutValue(K key, long adjust_amount, long put_amount) {
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
