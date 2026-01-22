#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/impl/HashFunctions.h"
#include "gnu/trove/procedure/TDoubleProcedure.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace impl {
namespace hash {


class TDoubleLongHash : public TPrimitiveHash {
public:
    static const long serialVersionUID = 1L;
   public transient double[] _set;
    double no_entry_key;
    long no_entry_value;
    bool consumeFreeSlot;

    public TDoubleLongHash() {
      this.no_entry_key = 0.0;
      this.no_entry_value = 0L;
   }

    public TDoubleLongHash(int initialCapacity) {
      super(initialCapacity);
      this.no_entry_key = 0.0;
      this.no_entry_value = 0L;
   }

    public TDoubleLongHash(int initialCapacity, float loadFactor) {
      super(initialCapacity, loadFactor);
      this.no_entry_key = 0.0;
      this.no_entry_value = 0L;
   }

    public TDoubleLongHash(int initialCapacity, float loadFactor, double no_entry_key, long no_entry_value) {
      super(initialCapacity, loadFactor);
      this.no_entry_key = no_entry_key;
      this.no_entry_value = no_entry_value;
   }

    double getNoEntryKey() {
      return this.no_entry_key;
   }

    long getNoEntryValue() {
      return this.no_entry_value;
   }

    int setUp(int initialCapacity) {
    int capacity = super.setUp(initialCapacity);
      this._set = new double[capacity];
    return capacity;
   }

    bool contains(double val) {
      return this.index(val) >= 0;
   }

    bool forEach(TDoubleProcedure procedure) {
      byte[] states = this._states;
      double[] set = this._set;
    int i = set.length;

      while (i-- > 0) {
         if (states[i] == 1 && !procedure.execute(set[i])) {
    return false;
         }
      }

    return true;
   }

    void removeAt(int index) {
      this._set[index] = this.no_entry_key;
      super.removeAt(index);
   }

    int index(double key) {
      byte[] states = this._states;
      double[] set = this._set;
    int length = states.length;
    int hash = HashFunctions.hash(key) & 2147483647;
    int index = hash % length;
    uint8_t state = states[index];
      if (state == 0) {
         return -1;
      } else {
    return state = = 1 && set[index] == key ? index : this.indexRehashed(key, index, hash, state);
      }
   }

    int indexRehashed(double key, int index, int hash, uint8_t state) {
    int length = this._set.length;
    int probe = 1 + hash % (length - 2);
    int loopIndex = index;

      do {
         index -= probe;
         if (index < 0) {
            index += length;
         }

         state = this._states[index];
         if (state == 0) {
            return -1;
         }

         if (key == this._set[index] && state != 2) {
    return index;
         }
      } while (index != loopIndex);

      return -1;
   }

    int insertKey(double val) {
    int hash = HashFunctions.hash(val) & 2147483647;
    int index = hash % this._states.length;
    uint8_t state = this._states[index];
      this.consumeFreeSlot = false;
      if (state == 0) {
         this.consumeFreeSlot = true;
         this.insertKeyAt(index, val);
    return index;
      } else {
    return state = = 1 && this._set[index] == val ? -index - 1 : this.insertKeyRehash(val, index, hash, state);
      }
   }

    int insertKeyRehash(double val, int index, int hash, uint8_t state) {
    int length = this._set.length;
    int probe = 1 + hash % (length - 2);
    int loopIndex = index;
    int firstRemoved = -1;

      do {
         if (state == 2 && firstRemoved == -1) {
            firstRemoved = index;
         }

         index -= probe;
         if (index < 0) {
            index += length;
         }

         state = this._states[index];
         if (state == 0) {
            if (firstRemoved != -1) {
               this.insertKeyAt(firstRemoved, val);
    return firstRemoved;
            }

            this.consumeFreeSlot = true;
            this.insertKeyAt(index, val);
    return index;
         }

         if (state == 1 && this._set[index] == val) {
            return -index - 1;
         }
      } while (index != loopIndex);

      if (firstRemoved != -1) {
         this.insertKeyAt(firstRemoved, val);
    return firstRemoved;
      } else {
         throw IllegalStateException("No free or removed slots available. Key set full?!!");
      }
   }

    void insertKeyAt(int index, double val) {
      this._set[index] = val;
      this._states[index] = 1;
   }

    int XinsertKey(double key) {
      byte[] states = this._states;
      double[] set = this._set;
    int length = states.length;
    int hash = HashFunctions.hash(key) & 2147483647;
    int index = hash % length;
    uint8_t state = states[index];
      this.consumeFreeSlot = false;
      if (state == 0) {
         this.consumeFreeSlot = true;
         set[index] = key;
         states[index] = 1;
    return index;
      } else if (state == 1 && set[index] == key) {
         return -index - 1;
      } else {
    int probe = 1 + hash % (length - 2);
         if (state != 2) {
            do {
               index -= probe;
               if (index < 0) {
                  index += length;
               }

               state = states[index];
            } while (state == 1 && set[index] != key);
         }

         if (state != 2) {
            if (state == 1) {
               return -index - 1;
            } else {
               this.consumeFreeSlot = true;
               set[index] = key;
               states[index] = 1;
    return index;
            }
         } else {
    int firstRemoved;
            for (firstRemoved = index; state != 0 && (state == 2 || set[index] != key); state = states[index]) {
               index -= probe;
               if (index < 0) {
                  index += length;
               }
            }

            if (state == 1) {
               return -index - 1;
            } else {
               set[index] = key;
               states[index] = 1;
    return firstRemoved;
            }
         }
      }
   }

    void writeExternal(ObjectOutput out) {
      out.writeByte(0);
      super.writeExternal(out);
      out.writeDouble(this.no_entry_key);
      out.writeLong(this.no_entry_value);
   }

    void readExternal(ObjectInput in) {
      in.readByte();
      super.readExternal(in);
      this.no_entry_key = in.readDouble();
      this.no_entry_value = in.readLong();
   }
}
} // namespace hash
} // namespace impl
} // namespace trove
} // namespace gnu
