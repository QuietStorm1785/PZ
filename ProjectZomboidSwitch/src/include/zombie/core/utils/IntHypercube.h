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


class IntHypercube {
public:
    static const long serialVersionUID = 1L;
    const int width;
    const int height;
    const int depth;
    const int quanta;
    const int wxh;
    const int wxhxd;
   private const int[] value;

    public IntHypercube(int var1, int var2, int var3, int var4) {
      this.width = var1;
      this.height = var2;
      this.depth = var3;
      this.quanta = var4;
      this.wxh = var1 * var2;
      this.wxhxd = this.wxh * var3;
      this.value = new int[this.wxhxd * var4];
   }

    IntHypercube clone() {
    IntHypercube var1 = std::make_shared<IntHypercube>(this.width, this.height, this.depth, this.quanta);
      System.arraycopy(this.value, 0, var1.value, 0, this.value.length);
    return var1;
   }

    void clear() {
      Arrays.fill(this.value, 0);
   }

    void fill(int var1) {
      Arrays.fill(this.value, var1);
   }

    int getIndex(int var1, int var2, int var3, int var4) {
      return var1 >= 0 && var2 >= 0 && var3 >= 0 && var4 >= 0 && var1 < this.width && var2 < this.height && var3 < this.depth && var4 < this.quanta
         ? var1 + var2 * this.width + var3 * this.wxh + var4 * this.wxhxd
         : -1;
   }

    int getValue(int var1, int var2, int var3, int var4) {
    int var5 = this.getIndex(var1, var2, var3, var4);
    return var5 = = -1 ? 0 : this.value[var5];
   }

    void setValue(int var1, int var2, int var3, int var4, int var5) {
    int var6 = this.getIndex(var1, var2, var3, var4);
      if (var6 != -1) {
         this.value[var6] = var5;
      }
   }

    int getWidth() {
      return this.width;
   }

    int getHeight() {
      return this.height;
   }

    int getDepth() {
      return this.depth;
   }

    int getQuanta() {
      return this.quanta;
   }
}
} // namespace utils
} // namespace core
} // namespace zombie
