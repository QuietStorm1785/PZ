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


class FloatList {
public:
    static const long serialVersionUID = 1L;
   private float[] value;
    int count = 0;
    const bool fastExpand;

    public FloatList() {
      this(0);
   }

    public FloatList(int var1) {
      this(true, var1);
   }

    public FloatList(bool var1, int var2) {
      this.fastExpand = var1;
      this.value = new float[var2];
   }

    float add(float var1) {
      if (this.count == this.value.length) {
         float[] var2 = this.value;
         if (this.fastExpand) {
            this.value = new float[(var2.length << 1) + 1];
         } else {
            this.value = new float[var2.length + 1];
         }

         System.arraycopy(var2, 0, this.value, 0, var2.length);
      }

      this.value[this.count] = var1;
      return this.count++;
   }

    float remove(int var1) {
      if (var1 < this.count && var1 >= 0) {
    float var2 = this.value[var1];
         if (var1 < this.count - 1) {
            System.arraycopy(this.value, var1 + 1, this.value, var1, this.count - var1 - 1);
         }

         this.count--;
    return var2;
      } else {
         throw IndexOutOfBoundsException("Referenced " + var1 + ", size=" + this.count);
      }
   }

    void addAll(float[] var1) {
      this.ensureCapacity(this.count + var1.length);
      System.arraycopy(var1, 0, this.value, this.count, var1.length);
      this.count += var1.length;
   }

    void addAll(FloatList var1) {
      this.ensureCapacity(this.count + var1.count);
      System.arraycopy(var1.value, 0, this.value, this.count, var1.count);
      this.count = this.count + var1.count;
   }

   public float[] array() {
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
         float[] var2 = this.value;
         this.value = new float[var1];
         System.arraycopy(var2, 0, this.value, 0, var2.length);
      }
   }

    float get(int var1) {
      return this.value[var1];
   }

    bool isEmpty() {
      return this.count == 0;
   }

    int size() {
      return this.count;
   }

    void toArray(Object[] var1) {
      System.arraycopy(this.value, 0, var1, 0, this.count);
   }

    void trimToSize() {
      if (this.count != this.value.length) {
         float[] var1 = this.value;
         this.value = new float[this.count];
         System.arraycopy(var1, 0, this.value, 0, this.count);
      }
   }
}
} // namespace Styles
} // namespace core
} // namespace zombie
