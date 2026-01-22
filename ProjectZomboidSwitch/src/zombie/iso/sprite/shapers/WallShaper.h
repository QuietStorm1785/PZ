#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Color.h"
#include "zombie/core/textures/TextureDraw.h"
#include "zombie/debug/DebugOptions.h"
#include <algorithm>

namespace zombie {
namespace iso {
namespace sprite {
namespace shapers {


class WallShaper {
public:
   public const int[] col = new int[4];
    int colTint = 0;

    void setTintColor(int var1) {
      this.colTint = var1;
   }

    void accept(TextureDraw var1) {
      if (DebugOptions.instance.Terrain.RenderTiles.IsoGridSquare.Walls.Lighting.getValue()) {
         var1.col0 = Color.blendBGR(var1.col0, this.col[0]);
         var1.col1 = Color.blendBGR(var1.col1, this.col[1]);
         var1.col2 = Color.blendBGR(var1.col2, this.col[2]);
         var1.col3 = Color.blendBGR(var1.col3, this.col[3]);
      }

      if (this.colTint != 0) {
         var1.col0 = Color.tintABGR(var1.col0, this.colTint);
         var1.col1 = Color.tintABGR(var1.col1, this.colTint);
         var1.col2 = Color.tintABGR(var1.col2, this.colTint);
         var1.col3 = Color.tintABGR(var1.col3, this.colTint);
      }
   }
}
} // namespace shapers
} // namespace sprite
} // namespace iso
} // namespace zombie
