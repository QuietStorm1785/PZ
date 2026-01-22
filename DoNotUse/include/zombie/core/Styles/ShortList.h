#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
namespace Styles {


class ShortList {
public:
    static const long serialVersionUID = 1L;
   private short[] value;
    short count = 0;
    const bool fastExpand;

    public ShortList() {
      this(0);
   }

    public ShortList(int var1) {
      this(true, var1);
   }

    public ShortList(bool var1, int var2) {
      this.fastExpand = var1;
      this.value = new short[var2];
   }

    short add(short var1) {
      if (this.count == this.value.length) {
         short[] var2 = this.value;
         if (this.fastExpand) {
            this.value = new short[(var2.length << 1) + 1];
         } else {
            this.value = new short[var2.length + 1];
         }

         System.arraycopy(var2, 0, this.value, 0, var2.length);
      }

      this.value[this.count] = var1;
      return this.count++;
   }

    short remove(int var1) {
      if (var1 < this.count && var1 >= 0) {
    short var2 = this.value[var1];
         if (var1 < this.count - 1) {
            System.arraycopy(this.value, var1 + 1, this.value, var1, this.count - var1 - 1);
         }

         this.count--;
    return var2;
      } else {
         throw IndexOutOfBoundsException("Referenced " + var1 + ", size=" + this.count);
      }
   }

    void addAll(short[] var1) {
      this.ensureCapacity(this.count + var1.length);
      System.arraycopy(var1, 0, this.value, this.count, var1.length);
      this.count = (short)(this.count + var1.length);
   }

    void addAll(ShortList var1) {
      this.ensureCapacity(this.count + var1.count);
      System.arraycopy(var1.value, 0, this.value, this.count, var1.count);
      this.count = (short)(this.count + var1.count);
   }

   public short[] array() {
      return this.value;
   }

    int capacity() {
      return this.value.length;
   }

    void clear() {
      this.count = 0;
   }

    void ensureCapacity(int var1) {
      if (this.value.length < var1) {
         short[] var2 = this.value;
         this.value = new short[var1];
         System.arraycopy(var2, 0, this.value, 0, var2.length);
      }
   }

    short get(int var1) {
      return this.value[var1];
   }

    bool isEmpty() {
      return this.count == 0;
   }

    int size() {
      return this.count;
   }

   public short[] toArray(short[] var1) {
      if (var1 == nullptr) {
         var1 = new short[this.count];
      }

      System.arraycopy(this.value, 0, var1, 0, this.count);
    return var1;
   }

    void trimToSize() {
      if (this.count != this.value.length) {
         short[] var1 = this.value;
         this.value = new short[this.count];
         System.arraycopy(var1, 0, this.value, 0, this.count);
      }
   }
}
} // namespace Styles
} // namespace core
} // namespace zombie
