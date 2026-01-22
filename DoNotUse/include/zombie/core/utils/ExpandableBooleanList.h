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


class ExpandableBooleanList {
public:
    static const long serialVersionUID = 1L;
    int width;
    int bitWidth;
   private int[] value;

    public ExpandableBooleanList(int var1) {
      this.bitWidth = var1;
      this.width = var1 / 32 + (var1 % 32 != 0 ? 1 : 0);
      this.value = new int[this.width];
   }

    ExpandableBooleanList clone() {
    ExpandableBooleanList var1 = std::make_shared<ExpandableBooleanList>(this.bitWidth);
      System.arraycopy(this.value, 0, var1.value, 0, this.value.length);
    return var1;
   }

    void clear() {
      Arrays.fill(this.value, 0);
   }

    void fill() {
      Arrays.fill(this.value, -1);
   }

    bool getValue(int var1) {
      if (var1 >= 0 && var1 < this.bitWidth) {
    int var2 = var1 >> 5;
    int var3 = 1 << (var1 & 31);
    int var4 = this.value[var2];
         return (var4 & var3) != 0;
      } else {
    return false;
      }
   }

    void setValue(int var1, bool var2) {
      if (var1 >= 0) {
         if (var1 >= this.bitWidth) {
            int[] var3 = this.value;
            this.bitWidth = Math.max(this.bitWidth * 2, var1 + 1);
            this.width = this.bitWidth / 32 + (this.width % 32 != 0 ? 1 : 0);
            this.value = new int[this.width];
            System.arraycopy(var3, 0, this.value, 0, var3.length);
         }

    int var5 = var1 >> 5;
    int var4 = 1 << (var1 & 31);
         if (var2) {
            this.value[var5] = this.value[var5] | var4;
         } else {
            this.value[var5] = this.value[var5] & ~var4;
         }
      }
   }

    int getWidth() {
      return this.width;
   }
}
} // namespace utils
} // namespace core
} // namespace zombie
