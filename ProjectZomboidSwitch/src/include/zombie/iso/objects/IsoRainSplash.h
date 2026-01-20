#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoObject/VisionResult.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteInstance.h"

namespace zombie {
namespace iso {
namespace objects {


class IsoRainSplash : public IsoObject {
public:
    int Age;

    bool Serialize() {
    return false;
   }

    public IsoRainSplash(IsoCell var1, IsoGridSquare var2) {
      if (var2 != nullptr) {
         if (!var2.getProperties().Is(IsoFlagType.HasRainSplashes)) {
            this.Age = 0;
            this.square = var2;
            this.offsetX = 0.0F;
            this.offsetY = 0.0F;
    int var3 = 1 + Rand.Next(2);
    uint8_t var4 = 16;
    uint8_t var5 = 8;

            for (int var6 = 0; var6 < var3; var6++) {
    float var7 = Rand.Next(0.1F, 0.9F);
    float var8 = Rand.Next(0.1F, 0.9F);
    short var9 = (short)(IsoUtils.XToScreen(var7, var8, 0.0F, 0) - var4 / 2);
    short var10 = (short)(IsoUtils.YToScreen(var7, var8, 0.0F, 0) - var5 / 2);
               this.AttachAnim("RainSplash", "00", 4, RainManager.RainSplashAnimDelay, -var9, -var10, true, 0, false, 0.7F, RainManager.RainSplashTintMod);
               ((IsoSpriteInstance)this.AttachedAnimSprite.get(var6)).Frame = (short)Rand.Next(4);
               ((IsoSpriteInstance)this.AttachedAnimSprite.get(var6)).setScale(Core.TileScale, Core.TileScale);
            }

            var2.getProperties().Set(IsoFlagType.HasRainSplashes);
            RainManager.AddRainSplash(this);
         }
      }
   }

    std::string getObjectName() {
      return "RainSplashes";
   }

    bool HasTooltip() {
    return false;
   }

    bool TestCollide(IsoMovingObject var1, IsoGridSquare var2) {
      return this.square == var2;
   }

    VisionResult TestVision(IsoGridSquare var1, IsoGridSquare var2) {
      return VisionResult.NoEffect;
   }

    void ChangeTintMod(ColorInfo var1) {
      if (this.AttachedAnimSprite != nullptr) {
    int var2 = 0;

         while (var2 < this.AttachedAnimSprite.size()) {
            var2++;
         }
      }
   }

    void update() {
      this.sx = this.sy = 0.0F;
      this.Age++;

      for (int var1 = 0; var1 < this.AttachedAnimSprite.size(); var1++) {
    IsoSpriteInstance var2 = (IsoSpriteInstance)this.AttachedAnimSprite.get(var1);
    IsoSprite var3 = var2.parentSprite;
         var2.update();
         var2.Frame = var2.Frame + var2.AnimFrameIncrease * (GameTime.instance.getMultipliedSecondsSinceLastUpdate() * 60.0F);
         if ((int)var2.Frame >= var3.CurrentAnim.Frames.size() && var3.Loop && var2.Looped) {
            var2.Frame = 0.0F;
         }
      }

      for (int var4 = 0; var4 < IsoPlayer.numPlayers; var4++) {
         if (Core.getInstance().RenderShader != nullptr && Core.getInstance().getOffscreenBuffer() != nullptr) {
            this.setAlphaAndTarget(var4, 0.25F);
         } else {
            this.setAlphaAndTarget(var4, 0.6F);
         }
      }
   }

    void Reset(IsoGridSquare var1) {
      if (var1 != nullptr) {
         if (!var1.getProperties().Is(IsoFlagType.HasRainSplashes)) {
            this.Age = 0;
            this.square = var1;
    int var2 = 1 + Rand.Next(2);
            if (this.AttachedAnimSprite != nullptr) {
    int var3 = 0;

               while (var3 < this.AttachedAnimSprite.size()) {
                  var3++;
               }
            }

            var1.getProperties().Set(IsoFlagType.HasRainSplashes);
            RainManager.AddRainSplash(this);
         }
      }
   }
}
} // namespace objects
} // namespace iso
} // namespace zombie
