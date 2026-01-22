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


class IsoRaindrop : public IsoObject {
public:
    int AnimSpriteIndex;
    float GravMod;
    int Life;
    float SplashY;
    float OffsetY;
    float Vel_Y;

    bool Serialize() {
    return false;
   }

    public IsoRaindrop(IsoCell var1, IsoGridSquare var2, bool var3) {
      if (var3) {
         if (var2 != nullptr) {
            if (!var2.getProperties().Is(IsoFlagType.HasRaindrop)) {
               this.Life = 0;
               this.square = var2;
    int var4 = 1 * Core.TileScale;
    int var5 = 64 * Core.TileScale;
    float var6 = Rand.Next(0.1F, 0.9F);
    float var7 = Rand.Next(0.1F, 0.9F);
    short var8 = (short)(IsoUtils.XToScreen(var6, var7, 0.0F, 0) - var4 / 2);
    short var9 = (short)(IsoUtils.YToScreen(var6, var7, 0.0F, 0) - var5);
               this.offsetX = 0.0F;
               this.offsetY = 0.0F;
               this.OffsetY = RainManager.RaindropStartDistance;
               this.SplashY = var9;
               this.AttachAnim("Rain", "00", 1, 0.0F, -var8, -var9, true, 0, false, 0.7F, RainManager.RaindropTintMod);
               if (this.AttachedAnimSprite != nullptr) {
                  this.AnimSpriteIndex = this.AttachedAnimSprite.size() - 1;
               } else {
                  this.AnimSpriteIndex = 0;
               }

               ((IsoSpriteInstance)this.AttachedAnimSprite.get(this.AnimSpriteIndex)).setScale(Core.TileScale, Core.TileScale);
               var2.getProperties().Set(IsoFlagType.HasRaindrop);
               this.Vel_Y = 0.0F;
    float var10 = 1000000.0F / Rand.Next(1000000) + 1.0E-5F;
               this.GravMod = -(RainManager.GravModMin + (RainManager.GravModMax - RainManager.GravModMin) * var10);
               RainManager.AddRaindrop(this);
            }
         }
      }
   }

    bool HasTooltip() {
    return false;
   }

    std::string getObjectName() {
      return "RainDrops";
   }

    bool TestCollide(IsoMovingObject var1, IsoGridSquare var2) {
      return this.square == var2;
   }

    VisionResult TestVision(IsoGridSquare var1, IsoGridSquare var2) {
      return VisionResult.NoEffect;
   }

    void ChangeTintMod(ColorInfo var1) {
   }

    void update() {
      this.sx = this.sy = 0.0F;
      this.Life++;

      for (int var1 = 0; var1 < this.AttachedAnimSprite.size(); var1++) {
    IsoSpriteInstance var2 = (IsoSpriteInstance)this.AttachedAnimSprite.get(var1);
         var2.update();
         var2.Frame = var2.Frame + var2.AnimFrameIncrease * (GameTime.instance.getMultipliedSecondsSinceLastUpdate() * 60.0F);
    IsoSprite var3 = var2.parentSprite;
         if ((int)var2.Frame >= var3.CurrentAnim.Frames.size() && var3.Loop && var2.Looped) {
            var2.Frame = 0.0F;
         }
      }

      this.Vel_Y = this.Vel_Y + this.GravMod * (GameTime.instance.getMultipliedSecondsSinceLastUpdate() * 60.0F);
      this.OffsetY = this.OffsetY + this.Vel_Y;
      if (this.AttachedAnimSprite != nullptr && this.AttachedAnimSprite.size() > this.AnimSpriteIndex && this.AnimSpriteIndex >= 0) {
         ((IsoSpriteInstance)this.AttachedAnimSprite.get(this.AnimSpriteIndex)).parentSprite.soffY = (short)(this.SplashY + (int)this.OffsetY);
      }

      if (this.OffsetY < 0.0F) {
         this.OffsetY = RainManager.RaindropStartDistance;
         this.Vel_Y = 0.0F;
    float var4 = 1000000.0F / Rand.Next(1000000) + 1.0E-5F;
         this.GravMod = -(RainManager.GravModMin + (RainManager.GravModMax - RainManager.GravModMin) * var4);
      }

      for (int var5 = 0; var5 < IsoPlayer.numPlayers; var5++) {
         if (Core.getInstance().RenderShader != nullptr && Core.getInstance().getOffscreenBuffer() != nullptr) {
            this.setAlphaAndTarget(var5, 0.55F);
         } else {
            this.setAlphaAndTarget(var5, 1.0F);
         }
      }
   }

    void Reset(IsoGridSquare var1, bool var2) {
      if (var2) {
         if (var1 != nullptr) {
            if (!var1.getProperties().Is(IsoFlagType.HasRaindrop)) {
               this.Life = 0;
               this.square = var1;
               this.OffsetY = RainManager.RaindropStartDistance;
               if (this.AttachedAnimSprite != nullptr) {
                  this.AnimSpriteIndex = this.AttachedAnimSprite.size() - 1;
               } else {
                  this.AnimSpriteIndex = 0;
               }

               var1.getProperties().Set(IsoFlagType.HasRaindrop);
               this.Vel_Y = 0.0F;
    float var3 = 1000000.0F / Rand.Next(1000000) + 1.0E-5F;
               this.GravMod = -(RainManager.GravModMin + (RainManager.GravModMax - RainManager.GravModMin) * var3);
               RainManager.AddRaindrop(this);
            }
         }
      }
   }
}
} // namespace objects
} // namespace iso
} // namespace zombie
