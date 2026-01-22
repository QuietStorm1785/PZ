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
#include "zombie/iso/sprite/shapers/SpritePadding/IsoPaddingSettings.h"
#include <algorithm>

namespace zombie {
namespace iso {
namespace sprite {
namespace shapers {


class FloorShaper {
public:
   protected const int[] col = new int[4];
    int colTint = 0;
    bool isShore = false;
   protected const float[] waterDepth = new float[4];

    void setVertColors(int var1, int var2, int var3, int var4) {
      this.col[0] = var1;
      this.col[1] = var2;
      this.col[2] = var3;
      this.col[3] = var4;
   }

    void setAlpha4(float var1) {
    int var2 = (int)(var1 * 255.0F) & 0xFF;
      this.col[0] = this.col[0] & 16777215 | var2 << 24;
      this.col[1] = this.col[1] & 16777215 | var2 << 24;
      this.col[2] = this.col[2] & 16777215 | var2 << 24;
      this.col[3] = this.col[3] & 16777215 | var2 << 24;
   }

    void setShore(bool var1) {
      this.isShore = var1;
   }

    void setWaterDepth(float var1, float var2, float var3, float var4) {
      this.waterDepth[0] = var1;
      this.waterDepth[1] = var2;
      this.waterDepth[2] = var3;
      this.waterDepth[3] = var4;
   }

    void setTintColor(int var1) {
      this.colTint = var1;
   }

    void accept(TextureDraw var1) {
      if (DebugOptions.instance.Terrain.RenderTiles.IsoGridSquare.Floor.Lighting.getValue()) {
         var1.col0 = Color.blendBGR(var1.col0, this.col[0]);
         var1.col1 = Color.blendBGR(var1.col1, this.col[1]);
         var1.col2 = Color.blendBGR(var1.col2, this.col[2]);
         var1.col3 = Color.blendBGR(var1.col3, this.col[3]);
      }

      if (this.isShore && DebugOptions.instance.Terrain.RenderTiles.IsoGridSquare.ShoreFade.getValue()) {
         var1.col0 = Color.setAlphaChannelToABGR(var1.col0, 1.0F - this.waterDepth[0]);
         var1.col1 = Color.setAlphaChannelToABGR(var1.col1, 1.0F - this.waterDepth[1]);
         var1.col2 = Color.setAlphaChannelToABGR(var1.col2, 1.0F - this.waterDepth[2]);
         var1.col3 = Color.setAlphaChannelToABGR(var1.col3, 1.0F - this.waterDepth[3]);
      }

      if (this.colTint != 0) {
         var1.col0 = Color.tintABGR(var1.col0, this.colTint);
         var1.col1 = Color.tintABGR(var1.col1, this.colTint);
         var1.col2 = Color.tintABGR(var1.col2, this.colTint);
         var1.col3 = Color.tintABGR(var1.col3, this.colTint);
      }

      SpritePadding.applyIsoPadding(var1, this.getIsoPaddingSettings());
   }

    IsoPaddingSettings getIsoPaddingSettings() {
      return SpritePaddingSettings.getSettings().IsoPadding;
   }
}
} // namespace shapers
} // namespace sprite
} // namespace iso
} // namespace zombie
