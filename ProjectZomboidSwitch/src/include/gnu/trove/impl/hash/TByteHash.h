#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/impl/Constants.h"
#include "gnu/trove/impl/HashFunctions.h"
#include "gnu/trove/procedure/TByteProcedure.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace impl {
namespace hash {


class TByteHash : public TPrimitiveHash {
public:
    static const long serialVersionUID = 1L;
   public transient byte[] _set;
    uint8_t no_entry_value;
    bool consumeFreeSlot;

    public TByteHash() {
      this.no_entry_value = Constants.DEFAULT_BYTE_NO_ENTRY_VALUE;
      if (this.no_entry_value != 0) {
         Arrays.fill(this._set, this.no_entry_value);
      }
   }

    public TByteHash(int initialCapacity) {
      super(initialCapacity);
      this.no_entry_value = Constants.DEFAULT_BYTE_NO_ENTRY_VALUE;
      if (this.no_entry_value != 0) {
         Arrays.fill(this._set, this.no_entry_value);
      }
   }

    public TByteHash(int initialCapacity, float loadFactor) {
      super(initialCapacity, loadFactor);
      this.no_entry_value = Constants.DEFAULT_BYTE_NO_ENTRY_VALUE;
      if (this.no_entry_value != 0) {
         Arrays.fill(this._set, this.no_entry_value);
      }
   }

    public TByteHash(int initialCapacity, float loadFactor, uint8_t no_entry_value) {
      super(initialCapacity, loadFactor);
      this.no_entry_value = no_entry_value;
      if (no_entry_value != 0) {
         Arrays.fill(this._set, no_entry_value);
      }
   }

    uint8_t getNoEntryValue() {
      return this.no_entry_value;
   }

    int setUp(int initialCapacity) {
    int capacity = super.setUp(initialCapacity);
      this._set = new byte[capacity];
    return capacity;
   }

    bool contains(uint8_t val) {
      return this.index(val) >= 0;
   }

    bool forEach(TByteProcedure procedure) {
      byte[] states = this._states;
      byte[] set = this._set;
    int i = set.length;

      while (i-- > 0) {
         if (states[i] == 1 && !procedure.execute(set[i])) {
    return false;
         }
      }

    return true;
   }

    void removeAt(int index) {
      this._set[index] = this.no_entry_value;
      super.removeAt(index);
   }

    int index(uint8_t val) {
      byte[] states = this._states;
      byte[] set = this._set;
    int length = states.length;
    int hash = HashFunctions.hash(val) & 2147483647;
    int index = hash % length;
    uint8_t state = states[index];
      if (state == 0) {
         return -1;
      } else {
    return state = = 1 && set[index] == val ? index : this.indexRehashed(val, index, hash, state);
      }
   }

    int indexRehashed(uint8_t key, int index, int hash, uint8_t state) {
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

    int insertKey(uint8_t val) {
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

    int insertKeyRehash(uint8_t val, int index, int hash, uint8_t state) {
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

    void insertKeyAt(int index, uint8_t val) {
      this._set[index] = val;
      this._states[index] = 1;
   }
}
} // namespace hash
} // namespace impl
} // namespace trove
} // namespace gnu
