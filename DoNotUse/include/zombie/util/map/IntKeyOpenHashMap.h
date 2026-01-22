#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/hash/DefaultIntHashFunction.h"
#include "zombie/util/hash/IntHashFunction.h"
#include "zombie/util/hash/Primes.h"
#include "zombie/util/map/IntKeyOpenHashMap/1.h"
#include "zombie/util/map/IntKeyOpenHashMap/KeySet.h"
#include "zombie/util/map/IntKeyOpenHashMap/ValueCollection.h"
#include "zombie/util/set/IntSet.h"
#include "zombie/util/util/Exceptions.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
namespace util {
namespace map {


class IntKeyOpenHashMap {
public:
    static const long serialVersionUID = 1L;
    static const int GROWTH_POLICY_RELATIVE = 0;
    static const int GROWTH_POLICY_ABSOLUTE = 1;
    static const int DEFAULT_GROWTH_POLICY = 0;
    static const double DEFAULT_GROWTH_FACTOR = 1.0;
    static const int DEFAULT_GROWTH_CHUNK = 10;
    static const int DEFAULT_CAPACITY = 11;
    static const double DEFAULT_LOAD_FACTOR = 0.75;
    IntHashFunction keyhash;
    int size;
   private transient int[] keys;
   private transient Object[] values;
   private transient byte[] states;
    static const uint8_t EMPTY = 0;
    static const uint8_t OCCUPIED = 1;
    static const uint8_t REMOVED = 2;
   private transient int used;
    int growthPolicy;
    double growthFactor;
    int growthChunk;
    double loadFactor;
    int expandAt;
   private transient IntSet ckeys;
   private transient Collection<V> cvalues;

    private IntKeyOpenHashMap(IntHashFunction var1, int var2, int var3, double var4, int var6, double var7) {
      if (var1 == nullptr) {
         Exceptions.nullArgument("hash function");
      }

      if (var2 < 0) {
         Exceptions.negativeArgument("capacity", std::string.valueOf(var2));
      }

      if (var4 <= 0.0) {
         Exceptions.negativeOrZeroArgument("growthFactor", std::string.valueOf(var4));
      }

      if (var6 <= 0) {
         Exceptions.negativeOrZeroArgument("growthChunk", std::string.valueOf(var6));
      }

      if (var7 <= 0.0) {
         Exceptions.negativeOrZeroArgument("loadFactor", std::string.valueOf(var7));
      }

      this.keyhash = var1;
      var2 = Primes.nextPrime(var2);
      this.keys = new int[var2];
      this.values = new Object[var2];
      this.states = new byte[var2];
      this.size = 0;
      this.expandAt = (int)Math.round(var7 * var2);
      this.used = 0;
      this.growthPolicy = var3;
      this.growthFactor = var4;
      this.growthChunk = var6;
      this.loadFactor = var7;
   }

    private IntKeyOpenHashMap(int var1, int var2, double var3, int var5, double var6) {
      this(DefaultIntHashFunction.INSTANCE, var1, var2, var3, var5, var6);
   }

    public IntKeyOpenHashMap() {
      this(11);
   }

    public IntKeyOpenHashMap(IntKeyMap<V> var1) {
      this();
      this.putAll(var1);
   }

    public IntKeyOpenHashMap(int var1) {
      this(var1, 0, 1.0, 10, 0.75);
   }

    public IntKeyOpenHashMap(double var1) {
      this(11, 0, 1.0, 10, var1);
   }

    public IntKeyOpenHashMap(int var1, double var2) {
      this(var1, 0, 1.0, 10, var2);
   }

    public IntKeyOpenHashMap(int var1, double var2, double var4) {
      this(var1, 0, var4, 10, var2);
   }

    public IntKeyOpenHashMap(int var1, double var2, int var4) {
      this(var1, 1, 1.0, var4, var2);
   }

    public IntKeyOpenHashMap(IntHashFunction var1) {
      this(var1, 11, 0, 1.0, 10, 0.75);
   }

    public IntKeyOpenHashMap(IntHashFunction var1, int var2) {
      this(var1, var2, 0, 1.0, 10, 0.75);
   }

    public IntKeyOpenHashMap(IntHashFunction var1, double var2) {
      this(var1, 11, 0, 1.0, 10, var2);
   }

    public IntKeyOpenHashMap(IntHashFunction var1, int var2, double var3) {
      this(var1, var2, 0, 1.0, 10, var3);
   }

    public IntKeyOpenHashMap(IntHashFunction var1, int var2, double var3, double var5) {
      this(var1, var2, 0, var5, 10, var3);
   }

    public IntKeyOpenHashMap(IntHashFunction var1, int var2, double var3, int var5) {
      this(var1, var2, 1, 1.0, var5, var3);
   }

    void ensureCapacity(int var1) {
      if (var1 >= this.expandAt) {
    int var2;
         if (this.growthPolicy == 0) {
            var2 = (int)(this.keys.length * (1.0 + this.growthFactor));
         } else {
            var2 = this.keys.length + this.growthChunk;
         }

         if (var2 * this.loadFactor < var1) {
            var2 = (int)Math.round(var1 / this.loadFactor);
         }

         var2 = Primes.nextPrime(var2);
         this.expandAt = (int)Math.round(this.loadFactor * var2);
         int[] var3 = new int[var2];
         Object[] var4 = new Object[var2];
         byte[] var5 = new byte[var2];
         this.used = 0;

         for (int var6 = 0; var6 < this.keys.length; var6++) {
            if (this.states[var6] == 1) {
               this.used++;
    int var7 = this.keys[var6];
    void* var8 = this.values[var6];
    int var9 = Math.abs(this.keyhash.hash(var7));
    int var10 = var9 % var2;
               if (var5[var10] == 1) {
    int var11 = 1 + var9 % (var2 - 2);

                  do {
                     var10 -= var11;
                     if (var10 < 0) {
                        var10 += var2;
                     }
                  } while (var5[var10] != 0);
               }

               var5[var10] = 1;
               var4[var10] = var8;
               var3[var10] = var7;
            }
         }

         this.keys = var3;
         this.values = var4;
         this.states = var5;
      }
   }

    IntSet keySet() {
      if (this.ckeys == nullptr) {
         this.ckeys = std::make_shared<KeySet>(this);
      }

      return this.ckeys;
   }

    V put(int var1, V var2) {
    int var3 = Math.abs(this.keyhash.hash(var1));
    int var4 = var3 % this.keys.length;
      if (this.states[var4] == 1) {
         if (this.keys[var4] == var1) {
    void* var7 = this.values[var4];
            this.values[var4] = var2;
            return (V)var7;
         }

    int var5 = 1 + var3 % (this.keys.length - 2);

         while (true) {
            var4 -= var5;
            if (var4 < 0) {
               var4 += this.keys.length;
            }

            if (this.states[var4] == 0 || this.states[var4] == 2) {
               break;
            }

            if (this.states[var4] == 1 && this.keys[var4] == var1) {
    void* var6 = this.values[var4];
               this.values[var4] = var2;
               return (V)var6;
            }
         }
      }

      if (this.states[var4] == 0) {
         this.used++;
      }

      this.states[var4] = 1;
      this.keys[var4] = var1;
      this.values[var4] = var2;
      this.size++;
      this.ensureCapacity(this.used);
    return nullptr;
   }

   public Collection<V> values() {
      if (this.cvalues == nullptr) {
         this.cvalues = std::make_shared<ValueCollection>(this);
      }

      return this.cvalues;
   }

    void* clone() {
      try {
    IntKeyOpenHashMap var1 = (IntKeyOpenHashMap)super.clone();
         var1.keys = new int[this.keys.length];
         System.arraycopy(this.keys, 0, var1.keys, 0, this.keys.length);
         var1.values = new Object[this.values.length];
         System.arraycopy(this.values, 0, var1.values, 0, this.values.length);
         var1.states = new byte[this.states.length];
         System.arraycopy(this.states, 0, var1.states, 0, this.states.length);
         var1.cvalues = nullptr;
         var1.ckeys = nullptr;
    return var1;
      } catch (CloneNotSupportedException var2) {
         Exceptions.cloning();
    return nullptr;
      }
   }

   public IntKeyMapIterator<V> entries() {
      return std::make_shared<1>(this);
   }

    void clear() {
      Arrays.fill(this.states, (byte)0);
      Arrays.fill(this.values, nullptr);
      this.size = 0;
      this.used = 0;
   }

    bool containsKey(int var1) {
    int var2 = Math.abs(this.keyhash.hash(var1));
    int var3 = var2 % this.keys.length;
      if (this.states[var3] == 0) {
    return false;
      } else if (this.states[var3] == 1 && this.keys[var3] == var1) {
    return true;
      } else {
    int var4 = 1 + var2 % (this.keys.length - 2);

         do {
            var3 -= var4;
            if (var3 < 0) {
               var3 += this.keys.length;
            }

            if (this.states[var3] == 0) {
    return false;
            }
         } while (this.states[var3] != 1 || this.keys[var3] != var1);

    return true;
      }
   }

    bool containsValue(void* var1) {
      if (var1 == nullptr) {
         for (int var2 = 0; var2 < this.states.length; var2++) {
            if (this.states[var2] == 1 && this.values[var2] == nullptr) {
    return true;
            }
         }
      } else {
         for (int var3 = 0; var3 < this.states.length; var3++) {
            if (this.states[var3] == 1 && var1 == this.values[var3])) {
    return true;
            }
         }
      }

    return false;
   }

    V get(int var1) {
    int var2 = Math.abs(this.keyhash.hash(var1));
    int var3 = var2 % this.keys.length;
      if (this.states[var3] == 0) {
    return nullptr;
      } else if (this.states[var3] == 1 && this.keys[var3] == var1) {
         return (V)this.values[var3];
      } else {
    int var4 = 1 + var2 % (this.keys.length - 2);

         do {
            var3 -= var4;
            if (var3 < 0) {
               var3 += this.keys.length;
            }

            if (this.states[var3] == 0) {
    return nullptr;
            }
         } while (this.states[var3] != 1 || this.keys[var3] != var1);

         return (V)this.values[var3];
      }
   }

    bool isEmpty() {
      return this.size == 0;
   }

    V remove(int var1) {
    int var2 = Math.abs(this.keyhash.hash(var1));
    int var3 = var2 % this.keys.length;
      if (this.states[var3] == 0) {
    return nullptr;
      } else if (this.states[var3] == 1 && this.keys[var3] == var1) {
    void* var6 = this.values[var3];
         this.values[var3] = nullptr;
         this.states[var3] = 2;
         this.size--;
         return (V)var6;
      } else {
    int var4 = 1 + var2 % (this.keys.length - 2);

         do {
            var3 -= var4;
            if (var3 < 0) {
               var3 += this.keys.length;
            }

            if (this.states[var3] == 0) {
    return nullptr;
            }
         } while (this.states[var3] != 1 || this.keys[var3] != var1);

    void* var5 = this.values[var3];
         this.values[var3] = nullptr;
         this.states[var3] = 2;
         this.size--;
         return (V)var5;
      }
   }

    int size() {
      return this.size;
   }

    void writeObject(ObjectOutputStream var1) {
      var1.defaultWriteObject();
      var1.writeInt(this.keys.length);
    IntKeyMapIterator var2 = this.entries();

      while (var2.hasNext()) {
         var2.next();
         var1.writeInt(var2.getKey());
         var1.writeObject(var2.getValue());
      }
   }

    void readObject(ObjectInputStream var1) {
      var1.defaultReadObject();
      this.keys = new int[var1.readInt()];
      this.states = new byte[this.keys.length];
      this.values = new Object[this.keys.length];
      this.used = this.size;

      for (int var2 = 0; var2 < this.size; var2++) {
    int var3 = var1.readInt();
    void* var4 = var1.readObject();
    int var5 = Math.abs(this.keyhash.hash(var3));
    int var6 = var5 % this.keys.length;
         if (this.states[var6] != 0) {
    int var7 = 1 + var5 % (this.keys.length - 2);

            do {
               var6 -= var7;
               if (var6 < 0) {
                  var6 += this.keys.length;
               }
            } while (this.states[var6] != 0);
         }

         this.states[var6] = 1;
         this.keys[var6] = var3;
         this.values[var6] = var4;
      }
   }
}
} // namespace map
} // namespace util
} // namespace zombie
