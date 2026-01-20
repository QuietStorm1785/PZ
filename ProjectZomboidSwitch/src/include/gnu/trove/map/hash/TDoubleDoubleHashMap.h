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
#include "gnu/trove/impl/hash/TDoubleDoubleHash.h"
#include "gnu/trove/iterator/TDoubleDoubleIterator.h"
#include "gnu/trove/map/TDoubleDoubleMap.h"
#include "gnu/trove/map/hash/TDoubleDoubleHashMap/1.h"
#include "gnu/trove/map/hash/TDoubleDoubleHashMap/TDoubleDoubleHashIterator.h"
#include "gnu/trove/map/hash/TDoubleDoubleHashMap/TKeyView.h"
#include "gnu/trove/map/hash/TDoubleDoubleHashMap/TValueView.h"
#include "gnu/trove/procedure/TDoubleDoubleProcedure.h"
#include "gnu/trove/procedure/TDoubleProcedure.h"
#include "gnu/trove/set/TDoubleSet.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class TDoubleDoubleHashMap : public TDoubleDoubleHash {
public:
    static const long serialVersionUID = 1L;
   protected transient double[] _values;

    public TDoubleDoubleHashMap() {
   }

    public TDoubleDoubleHashMap(int initialCapacity) {
      super(initialCapacity);
   }

    public TDoubleDoubleHashMap(int initialCapacity, float loadFactor) {
      super(initialCapacity, loadFactor);
   }

    public TDoubleDoubleHashMap(int initialCapacity, float loadFactor, double noEntryKey, double noEntryValue) {
      super(initialCapacity, loadFactor, noEntryKey, noEntryValue);
   }

    public TDoubleDoubleHashMap(double[] keys, double[] values) {
      super(Math.max(keys.length, values.length));
    int size = Math.min(keys.length, values.length);

      for (int i = 0; i < size; i++) {
         this.put(keys[i], values[i]);
      }
   }

    public TDoubleDoubleHashMap(TDoubleDoubleMap map) {
      super(map.size());
      if (dynamic_cast<TDoubleDoubleHashMap*>(map) != nullptr) {
    TDoubleDoubleHashMap hashmap = (TDoubleDoubleHashMap)map;
         this._loadFactor = hashmap._loadFactor;
         this.no_entry_key = hashmap.no_entry_key;
         this.no_entry_value = hashmap.no_entry_value;
         if (this.no_entry_key != 0.0) {
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
      double[] oldKeys = this._set;
      double[] oldVals = this._values;
      byte[] oldStates = this._states;
      this._set = new double[newCapacity];
      this._values = new double[newCapacity];
      this._states = new byte[newCapacity];
    int i = oldCapacity;

      while (i-- > 0) {
         if (oldStates[i] == 1) {
    double o = oldKeys[i];
    int index = this.insertKey(o);
            this._values[index] = oldVals[i];
         }
      }
   }

    double put(double key, double value) {
    int index = this.insertKey(key);
      return this.doPut(key, value, index);
   }

    double putIfAbsent(double key, double value) {
    int index = this.insertKey(key);
      return index < 0 ? this._values[-index - 1] : this.doPut(key, value, index);
   }

    double doPut(double key, double value, int index) {
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

      for (Entry<? : public double, ? : public double> entry : map.entrySet()) {
         this.put(entry.getKey(), entry.getValue());
      }
   }

    void putAll(TDoubleDoubleMap map) {
      this.ensureCapacity(map.size());
    TDoubleDoubleIterator iter = map.iterator();

      while (iter.hasNext()) {
         iter.advance();
         this.put(iter.key(), iter.value());
      }
   }

    double get(double key) {
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

    double remove(double key) {
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

    TDoubleSet keySet() {
      return std::make_shared<TKeyView>(this);
   }

   public double[] keys() {
      double[] keys = new double[this.size()];
      double[] k = this._set;
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

   public double[] keys(double[] array) {
    int size = this.size();
      if (array.length < size) {
         array = new double[size];
      }

      double[] keys = this._set;
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

    bool containsKey(double key) {
      return this.contains(key);
   }

    TDoubleDoubleIterator iterator() {
      return std::make_shared<TDoubleDoubleHashIterator>(this, this);
   }

    bool forEachKey(TDoubleProcedure procedure) {
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

    bool forEachEntry(TDoubleDoubleProcedure procedure) {
      byte[] states = this._states;
      double[] keys = this._set;
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

    bool retainEntries(TDoubleDoubleProcedure procedure) {
    bool modified = false;
      byte[] states = this._states;
      double[] keys = this._set;
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

    bool increment(double key) {
      return this.adjustValue(key, 1.0);
   }

    bool adjustValue(double key, double amount) {
    int index = this.index(key);
      if (index < 0) {
    return false;
      } else {
         this._values[index] = this._values[index] + amount;
    return true;
      }
   }

    double adjustOrPutValue(double key, double adjust_amount, double put_amount) {
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
      if (!(dynamic_cast<TDoubleDoubleMap*>(other) != nullptr)) {
    return false;
      } else {
    TDoubleDoubleMap that = (TDoubleDoubleMap)other;
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
    double key = this._set[i];
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
            out.writeDouble(this._set[i]);
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
    double key = in.readDouble();
    double val = in.readDouble();
         this.put(key, val);
      }
   }
}
} // namespace hash
} // namespace map
} // namespace trove
} // namespace gnu
