#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace zombie {
namespace iso {


class IsoPuddles {
public:
   const int[] squaresPerLevel = new int[8];
    int numSquares;
    int capacity = 512;
   float[] data;

    void clear() {
      this.numSquares = 0;
      Arrays.fill(this.squaresPerLevel, 0);
   }

    void addSquare(int var1, IsoPuddlesGeometry var2) {
    uint8_t var3 = 4;
      if (this.data == nullptr) {
         this.data = new float[this.capacity * var3 * 7];
      }

      if (this.numSquares + 1 > this.capacity) {
         this.capacity += 128;
         this.data = Arrays.copyOf(this.data, this.capacity * var3 * 7);
      }

    int var4 = this.numSquares * var3 * 7;

      for (int var5 = 0; var5 < 4; var5++) {
         this.data[var4++] = var2.pdne[var5];
         this.data[var4++] = var2.pdnw[var5];
         this.data[var4++] = var2.pda[var5];
         this.data[var4++] = var2.pnon[var5];
         this.data[var4++] = var2.x[var5];
         this.data[var4++] = var2.y[var5];
         this.data[var4++] = float.intBitsToFloat(var2.color[var5]);
      }

      this.numSquares++;
      this.squaresPerLevel[var1]++;
   }
}
} // namespace iso
} // namespace zombie
