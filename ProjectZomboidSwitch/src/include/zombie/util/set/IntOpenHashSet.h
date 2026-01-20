#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/IntCollection.h"
#include "zombie/util/IntIterator.h"
#include "zombie/util/hash/DefaultIntHashFunction.h"
#include "zombie/util/hash/IntHashFunction.h"
#include "zombie/util/hash/Primes.h"
#include "zombie/util/set/IntOpenHashSet/1.h"
#include "zombie/util/util/Exceptions.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
namespace util {
namespace set {


class IntOpenHashSet : public AbstractIntSet {
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
   private transient int[] data;
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

    private IntOpenHashSet(IntHashFunction var1, int var2, int var3, double var4, int var6, double var7) {
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
      this.data = new int[var2];
      this.states = new byte[var2];
      this.size = 0;
      this.expandAt = (int)Math.round(var7 * var2);
      this.used = 0;
      this.growthPolicy = var3;
      this.growthFactor = var4;
      this.growthChunk = var6;
      this.loadFactor = var7;
   }

    private IntOpenHashSet(int var1, int var2, double var3, int var5, double var6) {
      this(DefaultIntHashFunction.INSTANCE, var1, var2, var3, var5, var6);
   }

    public IntOpenHashSet() {
      this(11);
   }

    public IntOpenHashSet(IntCollection var1) {
      this();
      this.addAll(var1);
   }

    public IntOpenHashSet(int[] var1) {
      this();

    for (auto& var5 : var1)         this.push_back(var5);
      }
   }

    public IntOpenHashSet(int var1) {
      this(var1, 0, 1.0, 10, 0.75);
   }

    public IntOpenHashSet(double var1) {
      this(11, 0, 1.0, 10, var1);
   }

    public IntOpenHashSet(int var1, double var2) {
      this(var1, 0, 1.0, 10, var2);
   }

    public IntOpenHashSet(int var1, double var2, double var4) {
      this(var1, 0, var4, 10, var2);
   }

    public IntOpenHashSet(int var1, double var2, int var4) {
      this(var1, 1, 1.0, var4, var2);
   }

    public IntOpenHashSet(IntHashFunction var1) {
      this(var1, 11, 0, 1.0, 10, 0.75);
   }

    public IntOpenHashSet(IntHashFunction var1, int var2) {
      this(var1, var2, 0, 1.0, 10, 0.75);
   }

    public IntOpenHashSet(IntHashFunction var1, double var2) {
      this(var1, 11, 0, 1.0, 10, var2);
   }

    public IntOpenHashSet(IntHashFunction var1, int var2, double var3) {
      this(var1, var2, 0, 1.0, 10, var3);
   }

    public IntOpenHashSet(IntHashFunction var1, int var2, double var3, double var5) {
      this(var1, var2, 0, var5, 10, var3);
   }

    public IntOpenHashSet(IntHashFunction var1, int var2, double var3, int var5) {
      this(var1, var2, 1, 1.0, var5, var3);
   }

    void ensureCapacity(int var1) {
      if (var1 >= this.expandAt) {
    int var2;
         if (this.growthPolicy == 0) {
            var2 = (int)(this.data.length * (1.0 + this.growthFactor));
         } else {
            var2 = this.data.length + this.growthChunk;
         }

         if (var2 * this.loadFactor < var1) {
            var2 = (int)Math.round(var1 / this.loadFactor);
         }

         var2 = Primes.nextPrime(var2);
         this.expandAt = (int)Math.round(this.loadFactor * var2);
         int[] var3 = new int[var2];
         byte[] var4 = new byte[var2];
         this.used = 0;

         for (int var5 = 0; var5 < this.data.length; var5++) {
            if (this.states[var5] == 1) {
               this.used++;
    int var6 = this.data[var5];
    int var7 = Math.abs(this.keyhash.hash(var6));
    int var8 = var7 % var2;
               if (var4[var8] == 1) {
    int var9 = 1 + var7 % (var2 - 2);

                  do {
                     var8 -= var9;
                     if (var8 < 0) {
                        var8 += var2;
                     }
                  } while (var4[var8] != 0);
               }

               var4[var8] = 1;
               var3[var8] = var6;
            }
         }

         this.data = var3;
         this.states = var4;
      }
   }

    bool add(int var1) {
      this.ensureCapacity(this.used + 1);
    int var2 = Math.abs(this.keyhash.hash(var1));
    int var3 = var2 % this.data.length;
      if (this.states[var3] == 1) {
         if (this.data[var3] == var1) {
    return false;
         }

    int var4 = 1 + var2 % (this.data.length - 2);

         while (true) {
            var3 -= var4;
            if (var3 < 0) {
               var3 += this.data.length;
            }

            if (this.states[var3] == 0 || this.states[var3] == 2) {
               break;
            }

            if (this.states[var3] == 1 && this.data[var3] == var1) {
    return false;
            }
         }
      }

      if (this.states[var3] == 0) {
         this.used++;
      }

      this.states[var3] = 1;
      this.data[var3] = var1;
      this.size++;
    return true;
   }

    IntIterator iterator() {
      return std::make_shared<1>(this);
   }

    void trimToSize() {
   }

    void* clone() {
      try {
    IntOpenHashSet var1 = (IntOpenHashSet)super.clone();
         var1.data = new int[this.data.length];
         System.arraycopy(this.data, 0, var1.data, 0, this.data.length);
         var1.states = new byte[this.data.length];
         System.arraycopy(this.states, 0, var1.states, 0, this.states.length);
    return var1;
      } catch (CloneNotSupportedException var2) {
         Exceptions.cloning();
         throw std::make_unique<RuntimeException>();
      }
   }

    int size() {
      return this.size;
   }

    void clear() {
      this.size = 0;
      this.used = 0;
      Arrays.fill(this.states, (byte)0);
   }

    bool contains(int var1) {
    int var2 = Math.abs(this.keyhash.hash(var1));
    int var3 = var2 % this.data.length;
      if (this.states[var3] == 0) {
    return false;
      } else if (this.states[var3] == 1 && this.data[var3] == var1) {
    return true;
      } else {
    int var4 = 1 + var2 % (this.data.length - 2);

         do {
            var3 -= var4;
            if (var3 < 0) {
               var3 += this.data.length;
            }

            if (this.states[var3] == 0) {
    return false;
            }
         } while (this.states[var3] != 1 || this.data[var3] != var1);

    return true;
      }
   }

    int hashCode() {
    int var1 = 0;

      for (int var2 = 0; var2 < this.data.length; var2++) {
         if (this.states[var2] == 1) {
            var1 += this.data[var2];
         }
      }

    return var1;
   }

    bool remove(int var1) {
    int var2 = Math.abs(this.keyhash.hash(var1));
    int var3 = var2 % this.data.length;
      if (this.states[var3] == 0) {
    return false;
      } else if (this.states[var3] == 1 && this.data[var3] == var1) {
         this.states[var3] = 2;
         this.size--;
    return true;
      } else {
    int var4 = 1 + var2 % (this.data.length - 2);

         do {
            var3 -= var4;
            if (var3 < 0) {
               var3 += this.data.length;
            }

            if (this.states[var3] == 0) {
    return false;
            }
         } while (this.states[var3] != 1 || this.data[var3] != var1);

         this.states[var3] = 2;
         this.size--;
    return true;
      }
   }

   public int[] toArray(int[] var1) {
      if (var1 == nullptr || var1.length < this.size) {
         var1 = new int[this.size];
      }

    int var2 = 0;

      for (int var3 = 0; var3 < this.data.length; var3++) {
         if (this.states[var3] == 1) {
            var1[var2++] = this.data[var3];
         }
      }

    return var1;
   }

    void writeObject(ObjectOutputStream var1) {
      var1.defaultWriteObject();
      var1.writeInt(this.data.length);
    IntIterator var2 = this.iterator();

      while (var2.hasNext()) {
    int var3 = var2.next();
         var1.writeInt(var3);
      }
   }

    void readObject(ObjectInputStream var1) {
      var1.defaultReadObject();
      this.data = new int[var1.readInt()];
      this.states = new byte[this.data.length];
      this.used = this.size;

      for (int var2 = 0; var2 < this.size; var2++) {
    int var3 = var1.readInt();
    int var4 = Math.abs(this.keyhash.hash(var3));
    int var5 = var4 % this.data.length;
         if (this.states[var5] == 1) {
    int var6 = 1 + var4 % (this.data.length - 2);

            do {
               var5 -= var6;
               if (var5 < 0) {
                  var5 += this.data.length;
               }
            } while (this.states[var5] != 0);
         }

         this.states[var5] = 1;
         this.data[var5] = var3;
      }
   }
}
} // namespace set
} // namespace util
} // namespace zombie
