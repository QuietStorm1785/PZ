#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/function/TObjectFunction.h"
#include "gnu/trove/impl/Constants.h"
#include "gnu/trove/impl/HashFunctions.h"
#include "gnu/trove/impl/hash/TLongHash.h"
#include "gnu/trove/iterator/TLongObjectIterator.h"
#include "gnu/trove/map/TLongObjectMap.h"
#include "gnu/trove/map/hash/TLongObjectHashMap/1.h"
#include "gnu/trove/map/hash/TLongObjectHashMap/2.h"
#include "gnu/trove/map/hash/TLongObjectHashMap/KeyView.h"
#include "gnu/trove/map/hash/TLongObjectHashMap/TLongObjectHashIterator.h"
#include "gnu/trove/map/hash/TLongObjectHashMap/ValueView.h"
#include "gnu/trove/procedure/TLongObjectProcedure.h"
#include "gnu/trove/procedure/TLongProcedure.h"
#include "gnu/trove/procedure/TObjectProcedure.h"
#include "gnu/trove/set/TLongSet.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class TLongObjectHashMap {
public:
    static const long serialVersionUID = 1L;
   private const TLongObjectProcedure<V> PUT_ALL_PROC = std::make_shared<1>(this);
   protected transient V[] _values;
    long no_entry_key;

    public TLongObjectHashMap() {
   }

    public TLongObjectHashMap(int initialCapacity) {
      super(initialCapacity);
      this.no_entry_key = Constants.DEFAULT_LONG_NO_ENTRY_VALUE;
   }

    public TLongObjectHashMap(int initialCapacity, float loadFactor) {
      super(initialCapacity, loadFactor);
      this.no_entry_key = Constants.DEFAULT_LONG_NO_ENTRY_VALUE;
   }

    public TLongObjectHashMap(int initialCapacity, float loadFactor, long noEntryKey) {
      super(initialCapacity, loadFactor);
      this.no_entry_key = noEntryKey;
   }

    public TLongObjectHashMap(TLongObjectMap<? extends) {
      this(map.size(), 0.5F, map.getNoEntryKey());
      this.putAll(map);
   }

    int setUp(int initialCapacity) {
    int capacity = super.setUp(initialCapacity);
      this._values = (V[])(new Object[capacity]);
    return capacity;
   }

    void rehash(int newCapacity) {
    int oldCapacity = this._set.length;
      long[] oldKeys = this._set;
      V[] oldVals = this._values;
      byte[] oldStates = this._states;
      this._set = new long[newCapacity];
      this._values = (V[])(new Object[newCapacity]);
      this._states = new byte[newCapacity];
    int i = oldCapacity;

      while (i-- > 0) {
         if (oldStates[i] == 1) {
    long o = oldKeys[i];
    int index = this.insertKey(o);
            this._values[index] = oldVals[i];
         }
      }
   }

    long getNoEntryKey() {
      return this.no_entry_key;
   }

    bool containsKey(long key) {
      return this.contains(key);
   }

    bool containsValue(void* val) {
      byte[] states = this._states;
      V[] vals = this._values;
      if (nullptr == val) {
    int i = vals.length;

         while (i-- > 0) {
            if (states[i] == 1 && nullptr == vals[i]) {
    return true;
            }
         }
      } else {
    int i = vals.length;

         while (i-- > 0) {
            if (states[i] == 1 && (val == vals[i] || val == vals[i]))) {
    return true;
            }
         }
      }

    return false;
   }

    V get(long key) {
    int index = this.index(key);
      return index < 0 ? nullptr : this._values[index];
   }

    V put(long key, V value) {
    int index = this.insertKey(key);
      return this.doPut(value, index);
   }

    V putIfAbsent(long key, V value) {
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

    V remove(long key) {
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

    void putAll(Map<? extends, ? extends) {
      for (Entry<? : public int64_t, ? : public V> entry : map.entrySet()) {
         this.put(entry.getKey(), (V)entry.getValue());
      }
   }

    void putAll(TLongObjectMap<? extends) {
      map.forEachEntry(this.PUT_ALL_PROC);
   }

    void clear() {
      super.clear();
      Arrays.fill(this._set, 0, this._set.length, this.no_entry_key);
      Arrays.fill(this._states, 0, this._states.length, (byte)0);
      Arrays.fill(this._values, 0, this._values.length, nullptr);
   }

    TLongSet keySet() {
      return std::make_shared<KeyView>(this);
   }

   public long[] keys() {
      long[] keys = new long[this.size()];
      long[] k = this._set;
      byte[] states = this._states;
    int i = k.length;
    int j = 0;

      while (i-- > 0) {
         if (states[i] == 1) {
            keys[j++] = k[i];
         }
      }

    return keys;
   }

   public long[] keys(long[] dest) {
      if (dest.length < this._size) {
         dest = new long[this._size];
      }

      long[] k = this._set;
      byte[] states = this._states;
    int i = k.length;
    int j = 0;

      while (i-- > 0) {
         if (states[i] == 1) {
            dest[j++] = k[i];
         }
      }

    return dest;
   }

   public Collection<V> valueCollection() {
      return std::make_shared<ValueView>(this);
   }

   public Object[] values() {
      Object[] vals = new Object[this.size()];
      V[] v = this._values;
      byte[] states = this._states;
    int i = v.length;
    int j = 0;

      while (i-- > 0) {
         if (states[i] == 1) {
            vals[j++] = v[i];
         }
      }

    return vals;
   }

   public V[] values(V[] dest) {
      if (dest.length < this._size) {
         dest = (V[])((Object[])Array.newInstance(dest.getClass().getComponentType(), this._size));
      }

      V[] v = this._values;
      byte[] states = this._states;
    int i = v.length;
    int j = 0;

      while (i-- > 0) {
         if (states[i] == 1) {
            dest[j++] = v[i];
         }
      }

    return dest;
   }

   public TLongObjectIterator<V> iterator() {
      return std::make_shared<TLongObjectHashIterator>(this, this);
   }

    bool forEachKey(TLongProcedure procedure) {
      return this.forEach(procedure);
   }

    bool forEachValue(TObjectProcedure<? super) {
      byte[] states = this._states;
      V[] values = this._values;
    int i = values.length;

      while (i-- > 0) {
         if (states[i] == 1 && !procedure.execute(values[i])) {
    return false;
         }
      }

    return true;
   }

    bool forEachEntry(TLongObjectProcedure<? super) {
      byte[] states = this._states;
      long[] keys = this._set;
      V[] values = this._values;
    int i = keys.length;

      while (i-- > 0) {
         if (states[i] == 1 && !procedure.execute(keys[i], values[i])) {
    return false;
         }
      }

    return true;
   }

    bool retainEntries(TLongObjectProcedure<? super) {
    bool modified = false;
      byte[] states = this._states;
      long[] keys = this._set;
      V[] values = this._values;
      this.tempDisableAutoCompaction();

      try {
    int i = keys.length;

         while (i-- > 0) {
            if (states[i] == 1 && !procedure.execute(keys[i], values[i])) {
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
      byte[] states = this._states;
      V[] values = this._values;
    int i = values.length;

      while (i-- > 0) {
         if (states[i] == 1) {
            values[i] = (V)function.execute(values[i]);
         }
      }
   }

    bool equals(void* other) {
      if (!(dynamic_cast<TLongObjectMap*>(other) != nullptr)) {
    return false;
      } else {
    TLongObjectMap that = (TLongObjectMap)other;
         if (that.size() != this.size()) {
    return false;
         } else {
            try {
    TLongObjectIterator iter = this.iterator();

               while (iter.hasNext()) {
                  iter.advance();
    long key = iter.key();
    void* value = iter.value();
                  if (value == nullptr) {
                     if (that.get(key) != nullptr || !that.containsKey(key)) {
    return false;
                     }
                  } else if (!value == that.get(key))) {
    return false;
                  }
               }
            } catch (ClassCastException var7) {
            }

    return true;
         }
      }
   }

    int hashCode() {
    int hashcode = 0;
      V[] values = this._values;
      byte[] states = this._states;
    int i = values.length;

      while (i-- > 0) {
         if (states[i] == 1) {
            hashcode += HashFunctions.hash(this._set[i]) ^ (values[i] == nullptr ? 0 : values[i].hashCode());
         }
      }

    return hashcode;
   }

    void writeExternal(ObjectOutput out) {
      out.writeByte(0);
      super.writeExternal(out);
      out.writeLong(this.no_entry_key);
      out.writeInt(this._size);
    int i = this._states.length;

      while (i-- > 0) {
         if (this._states[i] == 1) {
            out.writeLong(this._set[i]);
            out.writeObject(this._values[i]);
         }
      }
   }

    void readExternal(ObjectInput in) {
      in.readByte();
      super.readExternal(in);
      this.no_entry_key = in.readLong();
    int size = in.readInt();
      this.setUp(size);

      while (size-- > 0) {
    long key = in.readLong();
    V val = (V)in.readObject();
         this.put(key, val);
      }
   }

    std::string toString() {
    std::stringstream buf = new std::stringstream("{");
      this.forEachEntry(std::make_shared<2>(this, buf));
      buf.append("}");
      return buf;
   }
}
} // namespace hash
} // namespace map
} // namespace trove
} // namespace gnu
