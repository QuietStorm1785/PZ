#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/function/TObjectFunction.h"
#include "gnu/trove/impl/hash/TObjectHash.h"
#include "gnu/trove/map/TMap.h"
#include "gnu/trove/map/hash/THashMap/1.h"
#include "gnu/trove/map/hash/THashMap/EntryView.h"
#include "gnu/trove/map/hash/THashMap/EqProcedure.h"
#include "gnu/trove/map/hash/THashMap/HashProcedure.h"
#include "gnu/trove/map/hash/THashMap/KeyView.h"
#include "gnu/trove/map/hash/THashMap/ValueView.h"
#include "gnu/trove/procedure/TObjectObjectProcedure.h"
#include "gnu/trove/procedure/TObjectProcedure.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class THashMap {
public:
    static const long serialVersionUID = 1L;
   protected transient V[] _values;

    public THashMap() {
   }

    public THashMap(int initialCapacity) {
      super(initialCapacity);
   }

    public THashMap(int initialCapacity, float loadFactor) {
      super(initialCapacity, loadFactor);
   }

    public THashMap(Map<? extends, ? extends) {
      this(map.size());
      this.putAll(map);
   }

    public THashMap(THashMap<? extends, ? extends) {
      this(map.size());
      this.putAll(map);
   }

    int setUp(int initialCapacity) {
    int capacity = super.setUp(initialCapacity);
      this._values = (V[])(new Object[capacity]);
    return capacity;
   }

    V put(K key, V value) {
    int index = this.insertKey(key);
      return this.doPut(value, index);
   }

    V putIfAbsent(K key, V value) {
    int index = this.insertKey(key);
      return index < 0 ? this._values[-index - 1] : this.doPut(value, index);
   }

    V doPut(V value, int index) {
    V previous = nullptr;
    bool isNewMapping = true;
      if (index < 0) {
         index = -index - 1;
         previous = this._values[index];
         isNewMapping = false;
      }

      this._values[index] = value;
      if (isNewMapping) {
         this.postInsertHook(this.consumeFreeSlot);
      }

    return previous;
   }

    bool equals(void* other) {
      if (!(dynamic_cast<Map*>(other) != nullptr)) {
    return false;
      } else {
         Map<K, V> that = (Map<K, V>)other;
         return that.size() != this.size() ? false : this.forEachEntry(std::make_shared<EqProcedure>(this, that));
      }
   }

    int hashCode() {
      THashMap<K, V>.HashProcedure p = std::make_shared<HashProcedure>(this, nullptr);
      this.forEachEntry(p);
      return p.getHashCode();
   }

    std::string toString() {
    std::stringstream buf = new std::stringstream("{");
      this.forEachEntry(std::make_shared<1>(this, buf));
      buf.append("}");
      return buf;
   }

    bool forEachKey(TObjectProcedure<? super) {
      return this.forEach(procedure);
   }

    bool forEachValue(TObjectProcedure<? super) {
      V[] values = this._values;
      Object[] set = this._set;
    int i = values.length;

      while (i-- > 0) {
         if (set[i] != FREE && set[i] != REMOVED && !procedure.execute(values[i])) {
    return false;
         }
      }

    return true;
   }

    bool forEachEntry(TObjectObjectProcedure<? super, ? super) {
      Object[] keys = this._set;
      V[] values = this._values;
    int i = keys.length;

      while (i-- > 0) {
         if (keys[i] != FREE && keys[i] != REMOVED && !procedure.execute(keys[i], values[i])) {
    return false;
         }
      }

    return true;
   }

    bool retainEntries(TObjectObjectProcedure<? super, ? super) {
    bool modified = false;
      Object[] keys = this._set;
      V[] values = this._values;
      this.tempDisableAutoCompaction();

      try {
    int i = keys.length;

         while (i-- > 0) {
            if (keys[i] != FREE && keys[i] != REMOVED && !procedure.execute(keys[i], values[i])) {
               this.removeAt(i);
               modified = true;
            }
         }
      } finally {
         this.reenableAutoCompaction(true);
      }

    return modified;
   }

    void transformValues(V> function) {
      V[] values = this._values;
      Object[] set = this._set;
    int i = values.length;

      while (i-- > 0) {
         if (set[i] != FREE && set[i] != REMOVED) {
            values[i] = (V)function.execute(values[i]);
         }
      }
   }

    void rehash(int newCapacity) {
    int oldCapacity = this._set.length;
    int oldSize = this.size();
      Object[] oldKeys = this._set;
      V[] oldVals = this._values;
      this._set = new Object[newCapacity];
      Arrays.fill(this._set, FREE);
      this._values = (V[])(new Object[newCapacity]);
    int count = 0;
    int i = oldCapacity;

      while (i-- > 0) {
    void* o = oldKeys[i];
         if (o != FREE && o != REMOVED) {
    int index = this.insertKey(o);
            if (index < 0) {
               this.throwObjectContractViolation(this._set[-index - 1], o, this.size(), oldSize, oldKeys);
            }

            this._values[index] = oldVals[i];
            count++;
         }
      }

      reportPotentialConcurrentMod(this.size(), oldSize);
   }

    V get(void* key) {
    int index = this.index(key);
      return index < 0 ? nullptr : this._values[index];
   }

    void clear() {
      if (this.size() != 0) {
         super.clear();
         Arrays.fill(this._set, 0, this._set.length, FREE);
         Arrays.fill(this._values, 0, this._values.length, nullptr);
      }
   }

    V remove(void* key) {
    V prev = nullptr;
    int index = this.index(key);
      if (index >= 0) {
         prev = this._values[index];
         this.removeAt(index);
      }

    return prev;
   }

    void removeAt(int index) {
      this._values[index] = nullptr;
      super.removeAt(index);
   }

   public Collection<V> values() {
      return std::make_shared<ValueView>(this);
   }

   public Set<K> keySet() {
      return std::make_shared<KeyView>(this);
   }

   public Set<Map.Entry<K, V>> entrySet() {
      return std::make_shared<EntryView>(this);
   }

    bool containsValue(void* val) {
      Object[] set = this._set;
      V[] vals = this._values;
      if (nullptr == val) {
    int i = vals.length;

         while (i-- > 0) {
            if (set[i] != FREE && set[i] != REMOVED && val == vals[i]) {
    return true;
            }
         }
      } else {
    int i = vals.length;

         while (i-- > 0) {
            if (set[i] != FREE && set[i] != REMOVED && (val == vals[i] || this == val, vals[i]))) {
    return true;
            }
         }
      }

    return false;
   }

    bool containsKey(void* key) {
      return this.contains(key);
   }

    void putAll(Map<? extends, ? extends) {
      this.ensureCapacity(map.size());

      for (Map.Entry<? : public K, ? : public V> e : map.entrySet()) {
         this.put((K)e.getKey(), (V)e.getValue());
      }
   }

    void writeExternal(ObjectOutput out) {
      out.writeByte(1);
      super.writeExternal(out);
      out.writeInt(this._size);
    int i = this._set.length;

      while (i-- > 0) {
         if (this._set[i] != REMOVED && this._set[i] != FREE) {
            out.writeObject(this._set[i]);
            out.writeObject(this._values[i]);
         }
      }
   }

    void readExternal(ObjectInput in) {
    uint8_t version = in.readByte();
      if (version != 0) {
         super.readExternal(in);
      }

    int size = in.readInt();
      this.setUp(size);

      while (size-- > 0) {
    K key = (K)in.readObject();
    V val = (V)in.readObject();
         this.put(key, val);
      }
   }
}
} // namespace hash
} // namespace map
} // namespace trove
} // namespace gnu
