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
#include "gnu/trove/impl/hash/TCharHash.h"
#include "gnu/trove/iterator/TCharObjectIterator.h"
#include "gnu/trove/map/TCharObjectMap.h"
#include "gnu/trove/map/hash/TCharObjectHashMap/1.h"
#include "gnu/trove/map/hash/TCharObjectHashMap/2.h"
#include "gnu/trove/map/hash/TCharObjectHashMap/KeyView.h"
#include "gnu/trove/map/hash/TCharObjectHashMap/TCharObjectHashIterator.h"
#include "gnu/trove/map/hash/TCharObjectHashMap/ValueView.h"
#include "gnu/trove/procedure/TCharObjectProcedure.h"
#include "gnu/trove/procedure/TCharProcedure.h"
#include "gnu/trove/procedure/TObjectProcedure.h"
#include "gnu/trove/set/TCharSet.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class TCharObjectHashMap {
public:
    static const long serialVersionUID = 1L;
   private const TCharObjectProcedure<V> PUT_ALL_PROC = std::make_shared<1>(this);
   protected transient V[] _values;
    char no_entry_key;

    public TCharObjectHashMap() {
   }

    public TCharObjectHashMap(int initialCapacity) {
      super(initialCapacity);
      this.no_entry_key = Constants.DEFAULT_CHAR_NO_ENTRY_VALUE;
   }

    public TCharObjectHashMap(int initialCapacity, float loadFactor) {
      super(initialCapacity, loadFactor);
      this.no_entry_key = Constants.DEFAULT_CHAR_NO_ENTRY_VALUE;
   }

    public TCharObjectHashMap(int initialCapacity, float loadFactor, char noEntryKey) {
      super(initialCapacity, loadFactor);
      this.no_entry_key = noEntryKey;
   }

    public TCharObjectHashMap(TCharObjectMap<? extends) {
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
      char[] oldKeys = this._set;
      V[] oldVals = this._values;
      byte[] oldStates = this._states;
      this._set = new char[newCapacity];
      this._values = (V[])(new Object[newCapacity]);
      this._states = new byte[newCapacity];
    int i = oldCapacity;

      while (i-- > 0) {
         if (oldStates[i] == 1) {
    char o = oldKeys[i];
    int index = this.insertKey(o);
            this._values[index] = oldVals[i];
         }
      }
   }

    char getNoEntryKey() {
      return this.no_entry_key;
   }

    bool containsKey(char key) {
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

    V get(char key) {
    int index = this.index(key);
      return index < 0 ? nullptr : this._values[index];
   }

    V put(char key, V value) {
    int index = this.insertKey(key);
      return this.doPut(value, index);
   }

    V putIfAbsent(char key, V value) {
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

    V remove(char key) {
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
      for (Entry<? : public char, ? : public V> entry : map.entrySet()) {
         this.put(entry.getKey(), (V)entry.getValue());
      }
   }

    void putAll(TCharObjectMap<? extends) {
      map.forEachEntry(this.PUT_ALL_PROC);
   }

    void clear() {
      super.clear();
      Arrays.fill(this._set, 0, this._set.length, this.no_entry_key);
      Arrays.fill(this._states, 0, this._states.length, (byte)0);
      Arrays.fill(this._values, 0, this._values.length, nullptr);
   }

    TCharSet keySet() {
      return std::make_shared<KeyView>(this);
   }

   public char[] keys() {
      char[] keys = new char[this.size()];
      char[] k = this._set;
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

   public char[] keys(char[] dest) {
      if (dest.length < this._size) {
         dest = new char[this._size];
      }

      char[] k = this._set;
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

   public TCharObjectIterator<V> iterator() {
      return std::make_shared<TCharObjectHashIterator>(this, this);
   }

    bool forEachKey(TCharProcedure procedure) {
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

    bool forEachEntry(TCharObjectProcedure<? super) {
      byte[] states = this._states;
      char[] keys = this._set;
      V[] values = this._values;
    int i = keys.length;

      while (i-- > 0) {
         if (states[i] == 1 && !procedure.execute(keys[i], values[i])) {
    return false;
         }
      }

    return true;
   }

    bool retainEntries(TCharObjectProcedure<? super) {
    bool modified = false;
      byte[] states = this._states;
      char[] keys = this._set;
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
      if (!(dynamic_cast<TCharObjectMap*>(other) != nullptr)) {
    return false;
      } else {
    TCharObjectMap that = (TCharObjectMap)other;
         if (that.size() != this.size()) {
    return false;
         } else {
            try {
    TCharObjectIterator iter = this.iterator();

               while (iter.hasNext()) {
                  iter.advance();
    char key = iter.key();
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
      out.writeChar(this.no_entry_key);
      out.writeInt(this._size);
    int i = this._states.length;

      while (i-- > 0) {
         if (this._states[i] == 1) {
            out.writeChar(this._set[i]);
            out.writeObject(this._values[i]);
         }
      }
   }

    void readExternal(ObjectInput in) {
      in.readByte();
      super.readExternal(in);
      this.no_entry_key = in.readChar();
    int size = in.readInt();
      this.setUp(size);

      while (size-- > 0) {
    char key = in.readChar();
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
