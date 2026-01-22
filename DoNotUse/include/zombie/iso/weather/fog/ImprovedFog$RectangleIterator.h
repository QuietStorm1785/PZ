#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Vector2i.h"
#include "zombie/core/math/PZMath.h"

namespace zombie {
namespace iso {
namespace weather {
namespace fog {


class ImprovedFog {
public:
    int curX = 0;
    int curY = 0;
    int sX;
    int sY;
    int rowLen = 0;
    bool altRow = false;
    int curRow = 0;
    int rowIndex = 0;
    int maxRows = 0;

   private ImprovedFog$RectangleIterator() {
   }

    void reset(int var1, int var2) {
      this.sX = 0;
      this.sY = 0;
      this.curX = 0;
      this.curY = 0;
      this.curRow = 0;
      this.altRow = false;
      this.rowIndex = 0;
      this.rowLen = (int)PZMath.ceil(var2 / 2.0F);
      this.maxRows = var1;
   }

    bool next(Vector2i var1) {
      if (this.rowLen > 0 && this.maxRows > 0 && this.curRow < this.maxRows) {
         var1.set(this.curX, this.curY);
         this.rowIndex++;
         if (this.rowIndex == this.rowLen) {
            this.rowLen = this.altRow ? this.rowLen - 1 : this.rowLen + 1;
            this.rowIndex = 0;
            this.sX = this.altRow ? this.sX + 1 : this.sX;
            this.sY = this.altRow ? this.sY : this.sY + 1;
            this.altRow = !this.altRow;
            this.curX = this.sX;
            this.curY = this.sY;
            this.curRow++;
            return this.curRow != this.maxRows;
         } else {
            this.curX++;
            this.curY--;
    return true;
         }
      } else {
         var1.set(0, 0);
    return false;
      }
   }
}
} // namespace fog
} // namespace weather
} // namespace iso
} // namespace zombie
