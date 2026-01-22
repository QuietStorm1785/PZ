#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/core/Core.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/iso/sprite/IsoDirectionFrame.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {


class IsoWallBloodSplat {
public:
    static const ColorInfo info = std::make_shared<ColorInfo>();
    float worldAge;
    IsoSprite sprite;

    public IsoWallBloodSplat() {
   }

    public IsoWallBloodSplat(float var1, IsoSprite var2) {
      this.worldAge = var1;
      this.sprite = var2;
   }

    void render(float var1, float var2, float var3, ColorInfo var4) {
      if (this.sprite != nullptr) {
         if (this.sprite.CurrentAnim != nullptr && !this.sprite.CurrentAnim.Frames.empty()) {
    int var5 = Core.TileScale;
    int var6 = 32 * var5;
    int var7 = 96 * var5;
            if (IsoSprite.globalOffsetX == -1.0F) {
               IsoSprite.globalOffsetX = -IsoCamera.frameState.OffX;
               IsoSprite.globalOffsetY = -IsoCamera.frameState.OffY;
            }

    float var8 = IsoUtils.XToScreen(var1, var2, var3, 0);
    float var9 = IsoUtils.YToScreen(var1, var2, var3, 0);
            var8 -= var6;
            var9 -= var7;
            var8 += IsoSprite.globalOffsetX;
            var9 += IsoSprite.globalOffsetY;
            if (!(var8 >= IsoCamera.frameState.OffscreenWidth) && !(var8 + 64 * var5 <= 0.0F)) {
               if (!(var9 >= IsoCamera.frameState.OffscreenHeight) && !(var9 + 128 * var5 <= 0.0F)) {
                  info.r = 0.7F * var4.r;
                  info.g = 0.9F * var4.g;
                  info.b = 0.9F * var4.b;
                  info.a = 0.4F;
    float var10 = (float)GameTime.getInstance().getWorldAgeHours();
    float var11 = var10 - this.worldAge;
                  if (var11 >= 0.0F && var11 < 72.0F) {
    float var12 = 1.0F - var11 / 72.0F;
                     info.r *= 0.2F + var12 * 0.8F;
                     info.g *= 0.2F + var12 * 0.8F;
                     info.b *= 0.2F + var12 * 0.8F;
                     info.a *= 0.25F + var12 * 0.75F;
                  } else {
                     info.r *= 0.2F;
                     info.g *= 0.2F;
                     info.b *= 0.2F;
                     info.a *= 0.25F;
                  }

                  info.a = Math.max(info.a, 0.15F);
                  ((IsoDirectionFrame)this.sprite.CurrentAnim.Frames.get(0)).render(var8, var9, IsoDirections.N, info, false, nullptr);
               }
            }
         }
      }
   }

    void save(ByteBuffer var1) {
      var1.putFloat(this.worldAge);
      var1.putInt(this.sprite.ID);
   }

    void load(ByteBuffer var1, int var2) {
      this.worldAge = var1.getFloat();
    int var3 = var1.getInt();
      this.sprite = IsoSprite.getSprite(IsoSpriteManager.instance, var3);
   }
}
} // namespace iso
} // namespace zombie
