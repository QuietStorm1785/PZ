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
#include "gnu/trove/impl/hash/TIntHash.h"
#include "gnu/trove/iterator/TIntObjectIterator.h"
#include "gnu/trove/map/TIntObjectMap.h"
#include "gnu/trove/map/hash/TIntObjectHashMap/1.h"
#include "gnu/trove/map/hash/TIntObjectHashMap/2.h"
#include "gnu/trove/map/hash/TIntObjectHashMap/KeyView.h"
#include "gnu/trove/map/hash/TIntObjectHashMap/TIntObjectHashIterator.h"
#include "gnu/trove/map/hash/TIntObjectHashMap/ValueView.h"
#include "gnu/trove/procedure/TIntObjectProcedure.h"
#include "gnu/trove/procedure/TIntProcedure.h"
#include "gnu/trove/procedure/TObjectProcedure.h"
#include "gnu/trove/set/TIntSet.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class TIntObjectHashMap {
public:
    static const long serialVersionUID = 1L;
   private const TIntObjectProcedure<V> PUT_ALL_PROC = std::make_shared<1>(this);
   protected transient V[] _values;
    int no_entry_key;

    public TIntObjectHashMap() {
   }

    public TIntObjectHashMap(int initialCapacity) {
      super(initialCapacity);
      this.no_entry_key = Constants.DEFAULT_INT_NO_ENTRY_VALUE;
   }

    public TIntObjectHashMap(int initialCapacity, float loadFactor) {
      super(initialCapacity, loadFactor);
      this.no_entry_key = Constants.DEFAULT_INT_NO_ENTRY_VALUE;
   }

    public TIntObjectHashMap(int initialCapacity, float loadFactor, int noEntryKey) {
      super(initialCapacity, loadFactor);
      this.no_entry_key = noEntryKey;
   }

    public TIntObjectHashMap(TIntObjectMap<? extends) {
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
      int[] oldKeys = this._set;
      V[] oldVals = this._values;
      byte[] oldStates = this._states;
      this._set = new int[newCapacity];
      this._values = (V[])(new Object[newCapacity]);
      this._states = new byte[newCapacity];
    int i = oldCapacity;

      while (i-- > 0) {
         if (oldStates[i] == 1) {
    int o = oldKeys[i];
    int index = this.insertKey(o);
            this._values[index] = oldVals[i];
         }
      }
   }

    int getNoEntryKey() {
      return this.no_entry_key;
   }

    bool containsKey(int key) {
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

    V get(int key) {
    int index = this.index(key);
      return index < 0 ? nullptr : this._values[index];
   }

    V put(int key, V value) {
    int index = this.insertKey(key);
      return this.doPut(value, index);
   }

    V putIfAbsent(int key, V value) {
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

    V remove(int key) {
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
      for (Entry<? : public int, ? : public V> entry : map.entrySet()) {
         this.put(entry.getKey(), (V)entry.getValue());
      }
   }

    void putAll(TIntObjectMap<? extends) {
      map.forEachEntry(this.PUT_ALL_PROC);
   }

    void clear() {
      super.clear();
      Arrays.fill(this._set, 0, this._set.length, this.no_entry_key);
      Arrays.fill(this._states, 0, this._states.length, (byte)0);
      Arrays.fill(this._values, 0, this._values.length, nullptr);
   }

    TIntSet keySet() {
      return std::make_shared<KeyView>(this);
   }

   public int[] keys() {
      int[] keys = new int[this.size()];
      int[] k = this._set;
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

   public int[] keys(int[] dest) {
      if (dest.length < this._size) {
         dest = new int[this._size];
      }

      int[] k = this._set;
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

   public TIntObjectIterator<V> iterator() {
      return std::make_shared<TIntObjectHashIterator>(this, this);
   }

    bool forEachKey(TIntProcedure procedure) {
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

    bool forEachEntry(TIntObjectProcedure<? super) {
      byte[] states = this._states;
      int[] keys = this._set;
      V[] values = this._values;
    int i = keys.length;

      while (i-- > 0) {
         if (states[i] == 1 && !procedure.execute(keys[i], values[i])) {
    return false;
         }
      }

    return true;
   }

    bool retainEntries(TIntObjectProcedure<? super) {
    bool modified = false;
      byte[] states = this._states;
      int[] keys = this._set;
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
      if (!(dynamic_cast<TIntObjectMap*>(other) != nullptr)) {
    return false;
      } else {
    TIntObjectMap that = (TIntObjectMap)other;
         if (that.size() != this.size()) {
    return false;
         } else {
            try {
    TIntObjectIterator iter = this.iterator();

               while (iter.hasNext()) {
                  iter.advance();
    int key = iter.key();
    void* value = iter.value();
                  if (value == nullptr) {
                     if (that.get(key) != nullptr || !that.containsKey(key)) {
    return false;
                     }
                  } else if (!value == that.get(key))) {
    return false;
                  }
               }
            } catch (ClassCastException var6) {
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
      out.writeInt(this.no_entry_key);
      out.writeInt(this._size);
    int i = this._states.length;

      while (i-- > 0) {
         if (this._states[i] == 1) {
            out.writeInt(this._set[i]);
            out.writeObject(this._values[i]);
         }
      }
   }

    void readExternal(ObjectInput in) {
      in.readByte();
      super.readExternal(in);
      this.no_entry_key = in.readInt();
    int size = in.readInt();
      this.setUp(size);

      while (size-- > 0) {
    int key = in.readInt();
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
