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


class IsoWater {
public:
    int numSquares;
    int capacity = 512;
   float[] data;

   private IsoWater$RenderData() {
   }

    void clear() {
      this.numSquares = 0;
   }

    void addSquare(IsoWaterGeometry var1) {
    int var2 = IsoCamera.frameState.playerIndex;
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
         this.data[var4++] = var1.depth[var5];
         this.data[var4++] = var1.flow[var5];
         this.data[var4++] = var1.speed[var5];
         this.data[var4++] = var1.IsExternal;
         this.data[var4++] = var1.x[var5];
         this.data[var4++] = var1.y[var5];
         if (var1.square != nullptr) {
    int var6 = var1.square.getVertLight((4 - var5) % 4, var2);
            this.data[var4++] = float.intBitsToFloat(var6);
         } else {
            var4++;
         }
      }

      this.numSquares++;
   }
}
} // namespace iso
} // namespace zombie
