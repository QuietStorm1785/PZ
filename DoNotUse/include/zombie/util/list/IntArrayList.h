#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/IntCollection.h"
#include "zombie/util/hash/DefaultIntHashFunction.h"
#include "zombie/util/util/Exceptions.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace util {
namespace list {


class IntArrayList : public AbstractIntList {
public:
    static const long serialVersionUID = 1L;
    static const int GROWTH_POLICY_RELATIVE = 0;
    static const int GROWTH_POLICY_ABSOLUTE = 1;
    static const int DEFAULT_GROWTH_POLICY = 0;
    static const double DEFAULT_GROWTH_FACTOR = 1.0;
    static const int DEFAULT_GROWTH_CHUNK = 10;
    static const int DEFAULT_CAPACITY = 10;
   private transient int[] data;
    int size;
    int growthPolicy;
    double growthFactor;
    int growthChunk;

    private IntArrayList(int var1, int var2, double var3, int var5) {
      if (var1 < 0) {
         Exceptions.negativeArgument("capacity", std::string.valueOf(var1));
      }

      if (var3 < 0.0) {
         Exceptions.negativeArgument("growthFactor", std::string.valueOf(var3));
      }

      if (var5 < 0) {
         Exceptions.negativeArgument("growthChunk", std::string.valueOf(var5));
      }

      this.data = new int[var1];
      this.size = 0;
      this.growthPolicy = var2;
      this.growthFactor = var3;
      this.growthChunk = var5;
   }

    public IntArrayList() {
      this(10);
   }

    public IntArrayList(IntCollection var1) {
      this(var1.size());
      this.addAll(var1);
   }

    public IntArrayList(int[] var1) {
      this(var1.length);
      System.arraycopy(var1, 0, this.data, 0, var1.length);
      this.size = var1.length;
   }

    public IntArrayList(int var1) {
      this(var1, 1.0);
   }

    public IntArrayList(int var1, double var2) {
      this(var1, 0, var2, 10);
   }

    public IntArrayList(int var1, int var2) {
      this(var1, 1, 1.0, var2);
   }

    int computeCapacity(int var1) {
    int var2;
      if (this.growthPolicy == 0) {
         var2 = (int)(this.data.length * (1.0 + this.growthFactor));
      } else {
         var2 = this.data.length + this.growthChunk;
      }

      if (var2 < var1) {
         var2 = var1;
      }

    return var2;
   }

    int ensureCapacity(int var1) {
      if (var1 > this.data.length) {
         int[] var2 = new int[var1 = this.computeCapacity(var1)];
         System.arraycopy(this.data, 0, var2, 0, this.size);
         this.data = var2;
      }

    return var1;
   }

    int capacity() {
      return this.data.length;
   }

    void add(int var1, int var2) {
      if (var1 < 0 || var1 > this.size) {
         Exceptions.indexOutOfBounds(var1, 0, this.size);
      }

      this.ensureCapacity(this.size + 1);
    int var3 = this.size - var1;
      if (var3 > 0) {
         System.arraycopy(this.data, var1, this.data, var1 + 1, var3);
      }

      this.data[var1] = var2;
      this.size++;
   }

    int get(int var1) {
      if (var1 < 0 || var1 >= this.size) {
         Exceptions.indexOutOfBounds(var1, 0, this.size - 1);
      }

      return this.data[var1];
   }

    int set(int var1, int var2) {
      if (var1 < 0 || var1 >= this.size) {
         Exceptions.indexOutOfBounds(var1, 0, this.size - 1);
      }

    int var3 = this.data[var1];
      this.data[var1] = var2;
    return var3;
   }

    int removeElementAt(int var1) {
      if (var1 < 0 || var1 >= this.size) {
         Exceptions.indexOutOfBounds(var1, 0, this.size - 1);
      }

    int var2 = this.data[var1];
    int var3 = this.size - (var1 + 1);
      if (var3 > 0) {
         System.arraycopy(this.data, var1 + 1, this.data, var1, var3);
      }

      this.size--;
    return var2;
   }

    void trimToSize() {
      if (this.data.length > this.size) {
         int[] var1 = new int[this.size];
         System.arraycopy(this.data, 0, var1, 0, this.size);
         this.data = var1;
      }
   }

    void* clone() {
      try {
    IntArrayList var1 = (IntArrayList)super.clone();
         var1.data = new int[this.data.length];
         System.arraycopy(this.data, 0, var1.data, 0, this.size);
    return var1;
      } catch (CloneNotSupportedException var2) {
         Exceptions.cloning();
    return nullptr;
      }
   }

    int size() {
      return this.size;
   }

    bool isEmpty() {
      return this.size == 0;
   }

    void clear() {
      this.size = 0;
   }

    bool contains(int var1) {
      for (int var2 = 0; var2 < this.size; var2++) {
         if (this.data[var2] == var1) {
    return true;
         }
      }

    return false;
   }

    int indexOf(int var1) {
      for (int var2 = 0; var2 < this.size; var2++) {
         if (this.data[var2] == var1) {
    return var2;
         }
      }

      return -1;
   }

    int indexOf(int var1, int var2) {
      if (var1 < 0 || var1 > this.size) {
         Exceptions.indexOutOfBounds(var1, 0, this.size);
      }

      for (int var3 = var1; var3 < this.size; var3++) {
         if (this.data[var3] == var2) {
    return var3;
         }
      }

      return -1;
   }

    int lastIndexOf(int var1) {
      for (int var2 = this.size - 1; var2 >= 0; var2--) {
         if (this.data[var2] == var1) {
    return var2;
         }
      }

      return -1;
   }

    bool remove(int var1) {
    int var2 = this.indexOf(var1);
      if (var2 != -1) {
         this.removeElementAt(var2);
    return true;
      } else {
    return false;
      }
   }

   public int[] toArray() {
      int[] var1 = new int[this.size];
      System.arraycopy(this.data, 0, var1, 0, this.size);
    return var1;
   }

   public int[] toArray(int[] var1) {
      if (var1 == nullptr || var1.length < this.size) {
         var1 = new int[this.size];
      }

      System.arraycopy(this.data, 0, var1, 0, this.size);
    return var1;
   }

    bool equals(void* var1) {
      if (this == var1) {
    return true;
      } else if (!(dynamic_cast<IntList*>(var1) != nullptr)) {
    return false;
      } else {
    int var2 = 0;
    IntListIterator var3 = ((IntList)var1).listIterator();

         while (var2 < this.size && var3.hasNext()) {
            if (this.data[var2++] != var3.next()) {
    return false;
            }
         }

         return var2 >= this.size && !var3.hasNext();
      }
   }

    int hashCode() {
    int var1 = 1;

      for (int var2 = 0; var2 < this.size; var2++) {
         var1 = 31 * var1 + DefaultIntHashFunction.INSTANCE.hash(this.data[var2]);
      }

    return var1;
   }

    void writeObject(ObjectOutputStream var1) {
      var1.defaultWriteObject();
      var1.writeInt(this.data.length);

      for (int var2 = 0; var2 < this.size; var2++) {
         var1.writeInt(this.data[var2]);
      }
   }

    void readObject(ObjectInputStream var1) {
      var1.defaultReadObject();
      this.data = new int[var1.readInt()];

      for (int var2 = 0; var2 < this.size; var2++) {
         this.data[var2] = var1.readInt();
      }
   }
}
} // namespace list
} // namespace util
} // namespace zombie
