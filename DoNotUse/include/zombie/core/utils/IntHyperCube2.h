#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace zombie {
namespace core {
namespace utils {


class IntHyperCube2 {
public:
    static const long serialVersionUID = 1L;
    const int width;
    const int height;
    const int depth;
    const int quanta;
    const int wxh;
    const int wxhxd;
   private const int[][][][] value;

    public IntHyperCube2(int var1, int var2, int var3, int var4) {
      this.width = var1;
      this.height = var2;
      this.depth = var3;
      this.quanta = var4;
      this.wxh = var1 * var2;
      this.wxhxd = this.wxh * var3;
      this.value = new int[var1][var2][var3][var4];
   }

    void clear() {
      Arrays.fill(this.value, int.valueOf(0));
   }

    void fill(int var1) {
      Arrays.fill(this.value, int.valueOf(var1));
   }

    int getIndex(int var1, int var2, int var3, int var4) {
      return var1 >= 0 && var2 >= 0 && var3 >= 0 && var4 >= 0 && var1 < this.width && var2 < this.height && var3 < this.depth && var4 < this.quanta
         ? var1 + var2 * this.width + var3 * this.wxh + var4 * this.wxhxd
         : -1;
   }

    int getValue(int var1, int var2, int var3, int var4) {
      return var1 >= 0 && var2 >= 0 && var3 >= 0 && var4 >= 0 && var1 < this.width && var2 < this.height && var3 < this.depth && var4 < this.quanta
         ? this.value[var1][var2][var3][var4]
         : 0;
   }

    void setValue(int var1, int var2, int var3, int var4, int var5) {
      this.value[var1][var2][var3][var4] = var5;
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
