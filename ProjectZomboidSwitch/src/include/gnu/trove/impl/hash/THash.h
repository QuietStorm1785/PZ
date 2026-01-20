#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/impl/HashFunctions.h"
#include "gnu/trove/impl/PrimeFinder.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace impl {
namespace hash {


class THash {
public:
    static const long serialVersionUID = -1792948471915530295L;
    static const float DEFAULT_LOAD_FACTOR = 0.5F;
    static const int DEFAULT_CAPACITY = 10;
   protected transient int _size;
   protected transient int _free;
    float _loadFactor;
    int _maxSize;
    int _autoCompactRemovesRemaining;
    float _autoCompactionFactor;
   protected transient boolean _autoCompactTemporaryDisable = false;

    public THash() {
      this(10, 0.5F);
   }

    public THash(int initialCapacity) {
      this(initialCapacity, 0.5F);
   }

    public THash(int initialCapacity, float loadFactor) {
      this._loadFactor = loadFactor;
      this._autoCompactionFactor = loadFactor;
      this.setUp(HashFunctions.fastCeil(initialCapacity / loadFactor));
   }

    bool isEmpty() {
    return 0 = = this._size;
   }

    int size() {
      return this._size;
   }

   public abstract int capacity();

    void ensureCapacity(int desiredCapacity) {
      if (desiredCapacity > this._maxSize - this.size()) {
         this.rehash(PrimeFinder.nextPrime(Math.max(this.size() + 1, HashFunctions.fastCeil((desiredCapacity + this.size()) / this._loadFactor) + 1)));
         this.computeMaxSize(this.capacity());
      }
   }

    void compact() {
      this.rehash(PrimeFinder.nextPrime(Math.max(this._size + 1, HashFunctions.fastCeil(this.size() / this._loadFactor) + 1)));
      this.computeMaxSize(this.capacity());
      if (this._autoCompactionFactor != 0.0F) {
         this.computeNextAutoCompactionAmount(this.size());
      }
   }

    void setAutoCompactionFactor(float factor) {
      if (factor < 0.0F) {
         throw IllegalArgumentException("Factor must be >= 0: " + factor);
      } else {
         this._autoCompactionFactor = factor;
      }
   }

    float getAutoCompactionFactor() {
      return this._autoCompactionFactor;
   }

    void trimToSize() {
      this.compact();
   }

    void removeAt(int index) {
      this._size--;
      if (this._autoCompactionFactor != 0.0F) {
         this._autoCompactRemovesRemaining--;
         if (!this._autoCompactTemporaryDisable && this._autoCompactRemovesRemaining <= 0) {
            this.compact();
         }
      }
   }

    void clear() {
      this._size = 0;
      this._free = this.capacity();
   }

    int setUp(int initialCapacity) {
    int capacity = PrimeFinder.nextPrime(initialCapacity);
      this.computeMaxSize(capacity);
      this.computeNextAutoCompactionAmount(initialCapacity);
    return capacity;
   }

   protected abstract void rehash(int var1);

    void tempDisableAutoCompaction() {
      this._autoCompactTemporaryDisable = true;
   }

    void reenableAutoCompaction(bool check_for_compaction) {
      this._autoCompactTemporaryDisable = false;
      if (check_for_compaction && this._autoCompactRemovesRemaining <= 0 && this._autoCompactionFactor != 0.0F) {
         this.compact();
      }
   }

    void computeMaxSize(int capacity) {
      this._maxSize = Math.min(capacity - 1, (int)(capacity * this._loadFactor));
      this._free = capacity - this._size;
   }

    void computeNextAutoCompactionAmount(int size) {
      if (this._autoCompactionFactor != 0.0F) {
         this._autoCompactRemovesRemaining = (int)(size * this._autoCompactionFactor + 0.5F);
      }
   }

    void postInsertHook(bool usedFreeSlot) {
      if (usedFreeSlot) {
         this._free--;
      }

      if (++this._size > this._maxSize || this._free == 0) {
    int newCapacity = this._size > this._maxSize ? PrimeFinder.nextPrime(this.capacity() << 1) : this.capacity();
         this.rehash(newCapacity);
         this.computeMaxSize(this.capacity());
      }
   }

    int calculateGrownCapacity() {
      return this.capacity() << 1;
   }

    void writeExternal(ObjectOutput out) {
      out.writeByte(0);
      out.writeFloat(this._loadFactor);
      out.writeFloat(this._autoCompactionFactor);
   }

    void readExternal(ObjectInput in) {
      in.readByte();
    float old_factor = this._loadFactor;
      this._loadFactor = in.readFloat();
      this._autoCompactionFactor = in.readFloat();
      if (old_factor != this._loadFactor) {
         this.setUp((int)Math.ceil(10.0F / this._loadFactor));
      }
   }
}
} // namespace hash
} // namespace impl
} // namespace trove
} // namespace gnu
