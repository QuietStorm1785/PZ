#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/function/TObjectFunction.h"
#include "gnu/trove/iterator/TShortObjectIterator.h"
#include "gnu/trove/map/TShortObjectMap.h"
#include "gnu/trove/procedure/TObjectProcedure.h"
#include "gnu/trove/procedure/TShortObjectProcedure.h"
#include "gnu/trove/procedure/TShortProcedure.h"
#include "gnu/trove/set/TShortSet.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace impl {
namespace sync {


class TSynchronizedShortObjectMap {
public:
    static const long serialVersionUID = 1978198479659022715L;
   private const TShortObjectMap<V> m;
    const void* mutex;
   private transient TShortSet keySet = nullptr;
   private transient Collection<V> values = nullptr;

    public TSynchronizedShortObjectMap(TShortObjectMap<V> m) {
      if (m == nullptr) {
         throw std::make_unique<NullPointerException>();
      } else {
         this.m = m;
         this.mutex = this;
      }
   }

    public TSynchronizedShortObjectMap(TShortObjectMap<V> m, void* mutex) {
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

    bool containsKey(short key) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.containsKey(key);
      }
   }

    bool containsValue(void* value) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.containsValue(value);
      }
   }

    V get(short key) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return (V)this.m.get(key);
      }
   }

    V put(short key, V value) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return (V)this.m.put(key, value);
      }
   }

    V remove(short key) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return (V)this.m.remove(key);
      }
   }

    void putAll(Map<? extends, ? extends) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.m.putAll(map);
      }
   }

    void putAll(TShortObjectMap<? extends) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.m.putAll(map);
      }
   }

    void clear() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.m.clear();
      }
   }

    TShortSet keySet() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         if (this.keySet == nullptr) {
            this.keySet = std::make_shared<TSynchronizedShortSet>(this.m.keySet(), this.mutex);
         }

         return this.keySet;
      }
   }

   public short[] keys() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.keys();
      }
   }

   public short[] keys(short[] array) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.keys(array);
      }
   }

   public Collection<V> valueCollection() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         if (this.values == nullptr) {
            this.values = std::make_shared<SynchronizedCollection>(this.m.valueCollection(), this.mutex);
         }

         return this.values;
      }
   }

   public Object[] values() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.values();
      }
   }

   public V[] values(V[] array) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return (V[])this.m.values(array);
      }
   }

   public TShortObjectIterator<V> iterator() {
      return this.m.iterator();
   }

    short getNoEntryKey() {
      return this.m.getNoEntryKey();
   }

    V putIfAbsent(short key, V value) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return (V)this.m.putIfAbsent(key, value);
      }
   }

    bool forEachKey(TShortProcedure procedure) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.forEachKey(procedure);
      }
   }

    bool forEachValue(TObjectProcedure<? super) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.forEachValue(procedure);
      }
   }

    bool forEachEntry(TShortObjectProcedure<? super) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.forEachEntry(procedure);
      }
   }

    void transformValues(V> function) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         this.m.transformValues(function);
      }
   }

    bool retainEntries(TShortObjectProcedure<? super) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.m.retainEntries(procedure);
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
