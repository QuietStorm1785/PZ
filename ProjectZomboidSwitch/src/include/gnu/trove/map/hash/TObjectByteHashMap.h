#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TByteCollection.h"
#include "gnu/trove/function/TByteFunction.h"
#include "gnu/trove/impl/Constants.h"
#include "gnu/trove/impl/HashFunctions.h"
#include "gnu/trove/impl/hash/TObjectHash.h"
#include "gnu/trove/iterator/TObjectByteIterator.h"
#include "gnu/trove/map/TObjectByteMap.h"
#include "gnu/trove/map/hash/TObjectByteHashMap/1.h"
#include "gnu/trove/map/hash/TObjectByteHashMap/2.h"
#include "gnu/trove/map/hash/TObjectByteHashMap/KeyView.h"
#include "gnu/trove/map/hash/TObjectByteHashMap/TByteValueCollection.h"
#include "gnu/trove/map/hash/TObjectByteHashMap/TObjectByteHashIterator.h"
#include "gnu/trove/procedure/TByteProcedure.h"
#include "gnu/trove/procedure/TObjectByteProcedure.h"
#include "gnu/trove/procedure/TObjectProcedure.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class TObjectByteHashMap {
public:
    static const long serialVersionUID = 1L;
   private const TObjectByteProcedure<K> PUT_ALL_PROC = std::make_shared<1>(this);
   protected transient byte[] _values;
    uint8_t no_entry_value;

    public TObjectByteHashMap() {
      this.no_entry_value = Constants.DEFAULT_BYTE_NO_ENTRY_VALUE;
   }

    public TObjectByteHashMap(int initialCapacity) {
      super(initialCapacity);
      this.no_entry_value = Constants.DEFAULT_BYTE_NO_ENTRY_VALUE;
   }

    public TObjectByteHashMap(int initialCapacity, float loadFactor) {
      super(initialCapacity, loadFactor);
      this.no_entry_value = Constants.DEFAULT_BYTE_NO_ENTRY_VALUE;
   }

    public TObjectByteHashMap(int initialCapacity, float loadFactor, uint8_t noEntryValue) {
      super(initialCapacity, loadFactor);
      this.no_entry_value = noEntryValue;
      if (this.no_entry_value != 0) {
         Arrays.fill(this._values, this.no_entry_value);
      }
   }

    public TObjectByteHashMap(TObjectByteMap<? extends) {
      this(map.size(), 0.5F, map.getNoEntryValue());
      if (dynamic_cast<TObjectByteHashMap*>(map) != nullptr) {
    TObjectByteHashMap hashmap = (TObjectByteHashMap)map;
         this._loadFactor = hashmap._loadFactor;
         this.no_entry_value = hashmap.no_entry_value;
         if (this.no_entry_value != 0) {
            Arrays.fill(this._values, this.no_entry_value);
         }

         this.setUp((int)Math.ceil(10.0F / this._loadFactor));
      }

      this.putAll(map);
   }

    int setUp(int initialCapacity) {
    int capacity = super.setUp(initialCapacity);
      this._values = new byte[capacity];
    return capacity;
   }

    void rehash(int newCapacity) {
    int oldCapacity = this._set.length;
      K[] oldKeys = (K[])this._set;
      byte[] oldVals = this._values;
      this._set = new Object[newCapacity];
      Arrays.fill(this._set, FREE);
      this._values = new byte[newCapacity];
      Arrays.fill(this._values, this.no_entry_value);
    int i = oldCapacity;

      while (i-- > 0) {
         if (oldKeys[i] != FREE && oldKeys[i] != REMOVED) {
    K o = oldKeys[i];
    int index = this.insertKey(o);
            if (index < 0) {
               this.throwObjectContractViolation(this._set[-index - 1], o);
            }

            this._set[index] = o;
            this._values[index] = oldVals[i];
         }
      }
   }

    uint8_t getNoEntryValue() {
      return this.no_entry_value;
   }

    bool containsKey(void* key) {
      return this.contains(key);
   }

    bool containsValue(uint8_t val) {
      Object[] keys = this._set;
      byte[] vals = this._values;
    int i = vals.length;

      while (i-- > 0) {
         if (keys[i] != FREE && keys[i] != REMOVED && val == vals[i]) {
    return true;
         }
      }

    return false;
   }

    uint8_t get(void* key) {
    int index = this.index(key);
      return index < 0 ? this.no_entry_value : this._values[index];
   }

    uint8_t put(K key, uint8_t value) {
    int index = this.insertKey(key);
      return this.doPut(value, index);
   }

    uint8_t putIfAbsent(K key, uint8_t value) {
    int index = this.insertKey(key);
      return index < 0 ? this._values[-index - 1] : this.doPut(value, index);
   }

    uint8_t doPut(uint8_t value, int index) {
    uint8_t previous = this.no_entry_value;
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

    uint8_t remove(void* key) {
    uint8_t prev = this.no_entry_value;
    int index = this.index(key);
      if (index >= 0) {
         prev = this._values[index];
         this.removeAt(index);
      }

    return prev;
   }

    void removeAt(int index) {
      this._values[index] = this.no_entry_value;
      super.removeAt(index);
   }

    void putAll(Map<? extends, ? extends) {
      for (Entry<? : public K, ? : public uint8_t> entry : map.entrySet()) {
         this.put((K)entry.getKey(), entry.getValue());
      }
   }

    void putAll(TObjectByteMap<? extends) {
      map.forEachEntry(this.PUT_ALL_PROC);
   }

    void clear() {
      super.clear();
      Arrays.fill(this._set, 0, this._set.length, FREE);
      Arrays.fill(this._values, 0, this._values.length, this.no_entry_value);
   }

   public Set<K> keySet() {
      return std::make_shared<KeyView>(this);
   }

   public Object[] keys() {
      K[] keys = (K[])(new Object[this.size()]);
      Object[] k = this._set;
    int i = k.length;
    int j = 0;

      while (i-- > 0) {
         if (k[i] != FREE && k[i] != REMOVED) {
            keys[j++] = (K)k[i];
         }
      }

    return keys;
   }

   public K[] keys(K[] a) {
    int size = this.size();
      if (a.length < size) {
         a = (K[])((Object[])Array.newInstance(a.getClass().getComponentType(), size));
      }

      Object[] k = this._set;
    int i = k.length;
    int j = 0;

      while (i-- > 0) {
         if (k[i] != FREE && k[i] != REMOVED) {
            a[j++] = (K)k[i];
         }
      }

    return a;
   }

    TByteCollection valueCollection() {
      return std::make_shared<TByteValueCollection>(this);
   }

   public byte[] values() {
      byte[] vals = new byte[this.size()];
      byte[] v = this._values;
      Object[] keys = this._set;
    int i = v.length;
    int j = 0;

      while (i-- > 0) {
         if (keys[i] != FREE && keys[i] != REMOVED) {
            vals[j++] = v[i];
         }
      }

    return vals;
   }

   public byte[] values(byte[] array) {
    int size = this.size();
      if (array.length < size) {
         array = new byte[size];
      }

      byte[] v = this._values;
      Object[] keys = this._set;
    int i = v.length;
    int j = 0;

      while (i-- > 0) {
         if (keys[i] != FREE && keys[i] != REMOVED) {
            array[j++] = v[i];
         }
      }

      if (array.length > size) {
         array[size] = this.no_entry_value;
      }

    return array;
   }

   public TObjectByteIterator<K> iterator() {
      return std::make_shared<TObjectByteHashIterator>(this, this);
   }

    bool increment(K key) {
      return this.adjustValue(key, (byte)1);
   }

    bool adjustValue(K key, uint8_t amount) {
    int index = this.index(key);
      if (index < 0) {
    return false;
      } else {
         this._values[index] = (byte)(this._values[index] + amount);
    return true;
      }
   }

    uint8_t adjustOrPutValue(K key, uint8_t adjust_amount, uint8_t put_amount) {
    int index = this.insertKey(key);
    bool isNewMapping;
    uint8_t newValue;
      if (index < 0) {
         index = -index - 1;
         newValue = this._values[index] = (byte)(this._values[index] + adjust_amount);
         isNewMapping = false;
      } else {
         newValue = this._values[index] = put_amount;
         isNewMapping = true;
      }

      if (isNewMapping) {
         this.postInsertHook(this.consumeFreeSlot);
      }

    return newValue;
   }

    bool forEachKey(TObjectProcedure<? super) {
      return this.forEach(procedure);
   }

    bool forEachValue(TByteProcedure procedure) {
      Object[] keys = this._set;
      byte[] values = this._values;
    int i = values.length;

      while (i-- > 0) {
         if (keys[i] != FREE && keys[i] != REMOVED && !procedure.execute(values[i])) {
    return false;
         }
      }

    return true;
   }

    bool forEachEntry(TObjectByteProcedure<? super) {
      Object[] keys = this._set;
      byte[] values = this._values;
    int i = keys.length;

      while (i-- > 0) {
         if (keys[i] != FREE && keys[i] != REMOVED && !procedure.execute(keys[i], values[i])) {
    return false;
         }
      }

    return true;
   }

    bool retainEntries(TObjectByteProcedure<? super) {
    bool modified = false;
      K[] keys = (K[])this._set;
      byte[] values = this._values;
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

    void transformValues(TByteFunction function) {
      Object[] keys = this._set;
      byte[] values = this._values;
    int i = values.length;

      while (i-- > 0) {
         if (keys[i] != nullptr && keys[i] != REMOVED) {
            values[i] = function.execute(values[i]);
         }
      }
   }

    bool equals(void* other) {
      if (!(dynamic_cast<TObjectByteMap*>(other) != nullptr)) {
    return false;
      } else {
    TObjectByteMap that = (TObjectByteMap)other;
         if (that.size() != this.size()) {
    return false;
         } else {
            try {
    TObjectByteIterator iter = this.iterator();

               while (iter.hasNext()) {
                  iter.advance();
    void* key = iter.key();
    uint8_t value = iter.value();
                  if (value == this.no_entry_value) {
                     if (that.get(key) != that.getNoEntryValue() || !that.containsKey(key)) {
    return false;
                     }
                  } else if (value != that.get(key)) {
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
      Object[] keys = this._set;
      byte[] values = this._values;
    int i = values.length;

      while (i-- > 0) {
         if (keys[i] != FREE && keys[i] != REMOVED) {
            hashcode += HashFunctions.hash(values[i]) ^ (keys[i] == nullptr ? 0 : keys[i].hashCode());
         }
      }

    return hashcode;
   }

    void writeExternal(ObjectOutput out) {
      out.writeByte(0);
      super.writeExternal(out);
      out.writeByte(this.no_entry_value);
      out.writeInt(this._size);
    int i = this._set.length;

      while (i-- > 0) {
         if (this._set[i] != REMOVED && this._set[i] != FREE) {
            out.writeObject(this._set[i]);
            out.writeByte(this._values[i]);
         }
      }
   }

    void readExternal(ObjectInput in) {
      in.readByte();
      super.readExternal(in);
      this.no_entry_value = in.readByte();
    int size = in.readInt();
      this.setUp(size);

      while (size-- > 0) {
    K key = (K)in.readObject();
    uint8_t val = in.readByte();
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
