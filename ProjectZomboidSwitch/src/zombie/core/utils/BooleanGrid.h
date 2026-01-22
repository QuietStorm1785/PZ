#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
namespace utils {


class BooleanGrid {
public:
    static const long serialVersionUID = 1L;
    const int width;
    const int height;
    const int bitWidth;
   private const int[] value;

    public BooleanGrid(int var1, int var2) {
      this.bitWidth = var1;
      this.width = var1 / 32 + (var1 % 32 != 0 ? 1 : 0);
      this.height = var2;
      this.value = new int[this.width * this.height];
   }

    BooleanGrid clone() {
    BooleanGrid var1 = std::make_shared<BooleanGrid>(this.bitWidth, this.height);
      System.arraycopy(this.value, 0, var1.value, 0, this.value.length);
    return var1;
   }

    void copy(BooleanGrid var1) {
      if (var1.bitWidth == this.bitWidth && var1.height == this.height) {
         System.arraycopy(var1.value, 0, this.value, 0, var1.value.length);
      } else {
         throw IllegalArgumentException("src must be same size as this: " + var1 + " cannot be copied into " + this);
      }
   }

    void clear() {
      Arrays.fill(this.value, 0);
   }

    void fill() {
      Arrays.fill(this.value, -1);
   }

    int getIndex(int var1, int var2) {
      return var1 >= 0 && var2 >= 0 && var1 < this.width && var2 < this.height ? var1 + var2 * this.width : -1;
   }

    bool getValue(int var1, int var2) {
      if (var1 < this.bitWidth && var1 >= 0 && var2 < this.height && var2 >= 0) {
    int var3 = var1 / 32;
    int var4 = 1 << (var1 & 31);
    int var5 = this.getIndex(var3, var2);
         if (var5 == -1) {
    return false;
         } else {
    int var6 = this.value[var5];
            return (var6 & var4) != 0;
         }
      } else {
    return false;
      }
   }

    void setValue(int var1, int var2, bool var3) {
      if (var1 < this.bitWidth && var1 >= 0 && var2 < this.height && var2 >= 0) {
    int var4 = var1 / 32;
    int var5 = 1 << (var1 & 31);
    int var6 = this.getIndex(var4, var2);
         if (var6 != -1) {
            if (var3) {
               this.value[var6] = this.value[var6] | var5;
            } else {
               this.value[var6] = this.value[var6] & ~var5;
            }
         }
      }
   }

    int getWidth() {
      return this.width;
   }

    int getHeight() {
      return this.height;
   }

    std::string toString() {
      return "BooleanGrid [width=" + this.width + ", height=" + this.height + ", bitWidth=" + this.bitWidth + "]";
   }

    void LoadFromByteBuffer(ByteBuffer var1) {
    int var2 = this.width * this.height;

      for (int var3 = 0; var3 < var2; var3++) {
         this.value[var3] = var1.getInt();
      }
   }

    void PutToByteBuffer(ByteBuffer var1) {
    int var2 = this.width * this.height;

      for (int var3 = 0; var3 < var2; var3++) {
         var1.putInt(this.value[var3]);
      }
   }
}
} // namespace utils
} // namespace core
} // namespace zombie
