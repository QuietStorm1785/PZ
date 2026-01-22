#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
namespace utils {


class ObjectGrid {
public:
    static const long serialVersionUID = 1L;
    const int width;
    const int height;
   private const Object[] value;

    public ObjectGrid(int var1, int var2) {
      this.width = var1;
      this.height = var2;
      this.value = new Object[var1 * var2];
   }

   public ObjectGrid<T> clone() throws CloneNotSupportedException {
    ObjectGrid var1 = std::make_shared<ObjectGrid>(this.width, this.height);
      System.arraycopy(this.value, 0, var1.value, 0, this.value.length);
    return var1;
   }

    void clear() {
      Arrays.fill(this.value, int.valueOf(0));
   }

    void fill(T var1) {
      Arrays.fill(this.value, var1);
   }

    int getIndex(int var1, int var2) {
      return var1 >= 0 && var2 >= 0 && var1 < this.width && var2 < this.height ? var1 + var2 * this.width : -1;
   }

    T getValue(int var1, int var2) {
    int var3 = this.getIndex(var1, var2);
      return (T)(var3 == -1 ? nullptr : this.value[var3]);
   }

    void setValue(int var1, int var2, T var3) {
    int var4 = this.getIndex(var1, var2);
      if (var4 != -1) {
         this.value[var4] = var3;
      }
   }

    int getWidth() {
      return this.width;
   }

    int getHeight() {
      return this.height;
   }
}
} // namespace utils
} // namespace core
} // namespace zombie
