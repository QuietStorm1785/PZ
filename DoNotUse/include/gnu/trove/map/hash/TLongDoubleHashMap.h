#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TDoubleCollection.h"
#include "gnu/trove/function/TDoubleFunction.h"
#include "gnu/trove/impl/HashFunctions.h"
#include "gnu/trove/impl/hash/TLongDoubleHash.h"
#include "gnu/trove/iterator/TLongDoubleIterator.h"
#include "gnu/trove/map/TLongDoubleMap.h"
#include "gnu/trove/map/hash/TLongDoubleHashMap/1.h"
#include "gnu/trove/map/hash/TLongDoubleHashMap/TKeyView.h"
#include "gnu/trove/map/hash/TLongDoubleHashMap/TLongDoubleHashIterator.h"
#include "gnu/trove/map/hash/TLongDoubleHashMap/TValueView.h"
#include "gnu/trove/procedure/TDoubleProcedure.h"
#include "gnu/trove/procedure/TLongDoubleProcedure.h"
#include "gnu/trove/procedure/TLongProcedure.h"
#include "gnu/trove/set/TLongSet.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class TLongDoubleHashMap : public TLongDoubleHash {
public:
    static const long serialVersionUID = 1L;
   protected transient double[] _values;

    public TLongDoubleHashMap() {
   }

    public TLongDoubleHashMap(int initialCapacity) {
      super(initialCapacity);
   }

    public TLongDoubleHashMap(int initialCapacity, float loadFactor) {
      super(initialCapacity, loadFactor);
   }

    public TLongDoubleHashMap(int initialCapacity, float loadFactor, long noEntryKey, double noEntryValue) {
      super(initialCapacity, loadFactor, noEntryKey, noEntryValue);
   }

    public TLongDoubleHashMap(long[] keys, double[] values) {
      super(Math.max(keys.length, values.length));
    int size = Math.min(keys.length, values.length);

      for (int i = 0; i < size; i++) {
         this.put(keys[i], values[i]);
      }
   }

    public TLongDoubleHashMap(TLongDoubleMap map) {
      super(map.size());
      if (dynamic_cast<TLongDoubleHashMap*>(map) != nullptr) {
    TLongDoubleHashMap hashmap = (TLongDoubleHashMap)map;
         this._loadFactor = hashmap._loadFactor;
         this.no_entry_key = hashmap.no_entry_key;
         this.no_entry_value = hashmap.no_entry_value;
         if (this.no_entry_key != 0L) {
            Arrays.fill(this._set, this.no_entry_key);
         }

         if (this.no_entry_value != 0.0) {
            Arrays.fill(this._values, this.no_entry_value);
         }

         this.setUp((int)Math.ceil(10.0F / this._loadFactor));
      }

      this.putAll(map);
   }

    int setUp(int initialCapacity) {
    int capacity = super.setUp(initialCapacity);
      this._values = new double[capacity];
    return capacity;
   }

    void rehash(int newCapacity) {
    int oldCapacity = this._set.length;
      long[] oldKeys = this._set;
      double[] oldVals = this._values;
      byte[] oldStates = this._states;
      this._set = new long[newCapacity];
      this._values = new double[newCapacity];
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

    double put(long key, double value) {
    int index = this.insertKey(key);
      return this.doPut(key, value, index);
   }

    double putIfAbsent(long key, double value) {
    int index = this.insertKey(key);
      return index < 0 ? this._values[-index - 1] : this.doPut(key, value, index);
   }

    double doPut(long key, double value, int index) {
    double previous = this.no_entry_value;
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

    void putAll(Map<? extends, ? extends) {
      this.ensureCapacity(map.size());

      for (Entry<? : public int64_t, ? : public double> entry : map.entrySet()) {
         this.put(entry.getKey(), entry.getValue());
      }
   }

    void putAll(TLongDoubleMap map) {
      this.ensureCapacity(map.size());
    TLongDoubleIterator iter = map.iterator();

      while (iter.hasNext()) {
         iter.advance();
         this.put(iter.key(), iter.value());
      }
   }

    double get(long key) {
    int index = this.index(key);
      return index < 0 ? this.no_entry_value : this._values[index];
   }

    void clear() {
      super.clear();
      Arrays.fill(this._set, 0, this._set.length, this.no_entry_key);
      Arrays.fill(this._values, 0, this._values.length, this.no_entry_value);
      Arrays.fill(this._states, 0, this._states.length, (byte)0);
   }

    bool isEmpty() {
    return 0 = = this._size;
   }

    double remove(long key) {
    double prev = this.no_entry_value;
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

    TLongSet keySet() {
      return std::make_shared<TKeyView>(this);
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

   public long[] keys(long[] array) {
    int size = this.size();
      if (array.length < size) {
         array = new long[size];
      }

      long[] keys = this._set;
      byte[] states = this._states;
    int i = keys.length;
    int j = 0;

      while (i-- > 0) {
         if (states[i] == 1) {
            array[j++] = keys[i];
         }
      }

    return array;
   }

    TDoubleCollection valueCollection() {
      return std::make_shared<TValueView>(this);
   }

   public double[] values() {
      double[] vals = new double[this.size()];
      double[] v = this._values;
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

   public double[] values(double[] array) {
    int size = this.size();
      if (array.length < size) {
         array = new double[size];
      }

      double[] v = this._values;
      byte[] states = this._states;
    int i = v.length;
    int j = 0;

      while (i-- > 0) {
         if (states[i] == 1) {
            array[j++] = v[i];
         }
      }

    return array;
   }

    bool containsValue(double val) {
      byte[] states = this._states;
      double[] vals = this._values;
    int i = vals.length;

      while (i-- > 0) {
         if (states[i] == 1 && val == vals[i]) {
    return true;
         }
      }

    return false;
   }

    bool containsKey(long key) {
      return this.contains(key);
   }

    TLongDoubleIterator iterator() {
      return std::make_shared<TLongDoubleHashIterator>(this, this);
   }

    bool forEachKey(TLongProcedure procedure) {
      return this.forEach(procedure);
   }

    bool forEachValue(TDoubleProcedure procedure) {
      byte[] states = this._states;
      double[] values = this._values;
    int i = values.length;

      while (i-- > 0) {
         if (states[i] == 1 && !procedure.execute(values[i])) {
    return false;
         }
      }

    return true;
   }

    bool forEachEntry(TLongDoubleProcedure procedure) {
      byte[] states = this._states;
      long[] keys = this._set;
      double[] values = this._values;
    int i = keys.length;

      while (i-- > 0) {
         if (states[i] == 1 && !procedure.execute(keys[i], values[i])) {
    return false;
         }
      }

    return true;
   }

    void transformValues(TDoubleFunction function) {
      byte[] states = this._states;
      double[] values = this._values;
    int i = values.length;

      while (i-- > 0) {
         if (states[i] == 1) {
            values[i] = function.execute(values[i]);
         }
      }
   }

    bool retainEntries(TLongDoubleProcedure procedure) {
    bool modified = false;
      byte[] states = this._states;
      long[] keys = this._set;
      double[] values = this._values;
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

    bool increment(long key) {
      return this.adjustValue(key, 1.0);
   }

    bool adjustValue(long key, double amount) {
    int index = this.index(key);
      if (index < 0) {
    return false;
      } else {
         this._values[index] = this._values[index] + amount;
    return true;
      }
   }

    double adjustOrPutValue(long key, double adjust_amount, double put_amount) {
    int index = this.insertKey(key);
    bool isNewMapping;
    double newValue;
      if (index < 0) {
         index = -index - 1;
         newValue = this._values[index] = this._values[index] + adjust_amount;
         isNewMapping = false;
      } else {
         newValue = this._values[index] = put_amount;
         isNewMapping = true;
      }

    uint8_t previousState = this._states[index];
      if (isNewMapping) {
         this.postInsertHook(this.consumeFreeSlot);
      }

    return newValue;
   }

    bool equals(void* other) {
      if (!(dynamic_cast<TLongDoubleMap*>(other) != nullptr)) {
    return false;
      } else {
    TLongDoubleMap that = (TLongDoubleMap)other;
         if (that.size() != this.size()) {
    return false;
         } else {
            double[] values = this._values;
            byte[] states = this._states;
    double this_no_entry_value = this.getNoEntryValue();
    double that_no_entry_value = that.getNoEntryValue();
    int i = values.length;

            while (i-- > 0) {
               if (states[i] == 1) {
    long key = this._set[i];
    double that_value = that.get(key);
    double this_value = values[i];
                  if (this_value != that_value && this_value != this_no_entry_value && that_value != that_no_entry_value) {
    return false;
                  }
               }
            }

    return true;
         }
      }
   }

    int hashCode() {
    int hashcode = 0;
      byte[] states = this._states;
    int i = this._values.length;

      while (i-- > 0) {
         if (states[i] == 1) {
            hashcode += HashFunctions.hash(this._set[i]) ^ HashFunctions.hash(this._values[i]);
         }
      }

    return hashcode;
   }

    std::string toString() {
    std::stringstream buf = new std::stringstream("{");
      this.forEachEntry(std::make_shared<1>(this, buf));
      buf.append("}");
      return buf;
   }

    void writeExternal(ObjectOutput out) {
      out.writeByte(0);
      super.writeExternal(out);
      out.writeInt(this._size);
    int i = this._states.length;

      while (i-- > 0) {
         if (this._states[i] == 1) {
            out.writeLong(this._set[i]);
            out.writeDouble(this._values[i]);
         }
      }
   }

    void readExternal(ObjectInput in) {
      in.readByte();
      super.readExternal(in);
    int size = in.readInt();
      this.setUp(size);

      while (size-- > 0) {
    long key = in.readLong();
    double val = in.readDouble();
         this.put(key, val);
      }
   }
}
} // namespace hash
} // namespace map
} // namespace trove
} // namespace gnu
