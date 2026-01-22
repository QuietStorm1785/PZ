#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Color.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/opengl/RenderSettings/PlayerRenderSettings.h"
#include "zombie/iso/Vector2.h"
#include "zombie/iso/weather/ClimateManager/ClimateFloat.h"
#include "zombie/iso/weather/WorldFlares/PlayerFlareLightInfo.h"
#include "zombie/iso/weather/fx/SteppedUpdateFloat.h"

namespace zombie {
namespace iso {
namespace weather {


class WorldFlares {
public:
    int id;
    float x;
    float y;
    int range;
    float windSpeed = 0.0F;
    ClimateColorInfo color = std::make_shared<ClimateColorInfo>(1.0F, 0.0F, 0.0F, 1.0F, 1.0F, 0.0F, 0.0F, 1.0F);
    bool hasLaunched = false;
    SteppedUpdateFloat intensity = std::make_shared<SteppedUpdateFloat>(0.0F, 0.01F, 0.0F, 1.0F);
    float maxLifeTime;
    float lifeTime;
    int nextRandomTargetIntens = 10;
    float perc = 0.0F;
   private PlayerFlareLightInfo[] infos = new PlayerFlareLightInfo[4];

   public WorldFlares$Flare() {
      for (int var1 = 0; var1 < this.infos.length; var1++) {
         this.infos[var1] = std::make_unique<PlayerFlareLightInfo>();
      }
   }

    int getId() {
      return this.id;
   }

    float getX() {
      return this.x;
   }

    float getY() {
      return this.y;
   }

    int getRange() {
      return this.range;
   }

    float getWindSpeed() {
      return this.windSpeed;
   }

    ClimateColorInfo getColor() {
      return this.color;
   }

    bool isHasLaunched() {
      return this.hasLaunched;
   }

    float getIntensity() {
      return this.intensity.value();
   }

    float getMaxLifeTime() {
      return this.maxLifeTime;
   }

    float getLifeTime() {
      return this.lifeTime;
   }

    float getPercent() {
      return this.perc;
   }

    float getIntensityPlayer(int var1) {
      return this.infos[var1].intensity;
   }

    float getLerpPlayer(int var1) {
      return this.infos[var1].lerp;
   }

    float getDistModPlayer(int var1) {
      return this.infos[var1].distMod;
   }

    ClimateColorInfo getColorPlayer(int var1) {
      return this.infos[var1].flareCol;
   }

    ClimateColorInfo getOutColorPlayer(int var1) {
      return this.infos[var1].outColor;
   }

    int GetDistance(int var1, int var2, int var3, int var4) {
      return (int)Math.sqrt(Math.pow(var1 - var3, 2.0) + Math.pow(var2 - var4, 2.0));
   }

    void update() {
      if (this.hasLaunched) {
         if (this.lifeTime > this.maxLifeTime) {
            this.hasLaunched = false;
            return;
         }

         this.perc = this.lifeTime / this.maxLifeTime;
         this.nextRandomTargetIntens = (int)(this.nextRandomTargetIntens - GameTime.instance.getMultiplier());
         if (this.nextRandomTargetIntens <= 0) {
            this.intensity.setTarget(Rand.Next(0.8F, 1.0F));
            this.nextRandomTargetIntens = Rand.Next(5, 30);
         }

         this.intensity.update(GameTime.instance.getMultiplier());
         if (this.windSpeed > 0.0F) {
            Vector2 var1 = std::make_shared<Vector2>(
               this.windSpeed / 60.0F * ClimateManager.getInstance().getWindIntensity() * (float)Math.sin(ClimateManager.getInstance().getWindAngleRadians()),
               this.windSpeed / 60.0F * ClimateManager.getInstance().getWindIntensity() * (float)Math.cos(ClimateManager.getInstance().getWindAngleRadians())
            );
            this.x = this.x + var1.x * GameTime.instance.getMultiplier();
            this.y = this.y + var1.y * GameTime.instance.getMultiplier();
         }

         for (int var6 = 0; var6 < 4; var6++) {
    PlayerFlareLightInfo var2 = this.infos[var6];
    IsoPlayer var3 = IsoPlayer.players[var6];
            if (var3 == nullptr) {
               var2.intensity = 0.0F;
            } else {
    int var4 = this.GetDistance((int)this.x, (int)this.y, (int)var3.getX(), (int)var3.getY());
               if (var4 > this.range) {
                  var2.intensity = 0.0F;
                  var2.lerp = 1.0F;
               } else {
                  var2.distMod = 1.0F - (float)var4 / this.range;
                  if (this.perc < 0.75F) {
                     var2.lerp = 0.0F;
                  } else {
                     var2.lerp = (this.perc - 0.75F) / 0.25F;
                  }

                  var2.intensity = this.intensity.value();
               }

    float var5 = (1.0F - var2.lerp) * var2.distMod * var2.intensity;
    ClimateFloat var10000 = ClimateManager.getInstance().dayLightStrength;
               var10000.finalValue = var10000.finalValue + (1.0F - ClimateManager.getInstance().dayLightStrength.finalValue) * var5;
               if (var3 != nullptr) {
                  var3.dirtyRecalcGridStackTime = 1.0F;
               }
            }
         }

         this.lifeTime = this.lifeTime + GameTime.instance.getMultiplier();
      }
   }

    void applyFlare(PlayerRenderSettings var1, int var2, IsoPlayer var3) {
    PlayerFlareLightInfo var4 = this.infos[var2];
      if (var4.distMod > 0.0F) {
    float var5 = 1.0F - var1.CM_DayLightStrength;
         var5 = var1.CM_NightStrength > var5 ? var1.CM_NightStrength : var5;
         var5 = PZMath.clamp(var5 * 2.0F, 0.0F, 1.0F);
    float var6 = 1.0F - var4.lerp;
         var6 *= var4.distMod;
    ClimateColorInfo var7 = var1.CM_GlobalLight;
         var4.outColor.setTo(var7);
    Color var10000 = var4.outColor.getExterior();
    float var10003 = var5 * var6 * var4.intensity;
         var10000.g = var4.outColor.getExterior().g * (1.0F - var10003 * 0.5F);
         var10000 = var4.outColor.getInterior();
         var10003 = var5 * var6 * var4.intensity;
         var10000.g = var4.outColor.getInterior().g * (1.0F - var10003 * 0.5F);
         var10000 = var4.outColor.getExterior();
         var10003 = var5 * var6 * var4.intensity;
         var10000.b = var4.outColor.getExterior().b * (1.0F - var10003 * 0.8F);
         var10000 = var4.outColor.getInterior();
         var10003 = var5 * var6 * var4.intensity;
         var10000.b = var4.outColor.getInterior().b * (1.0F - var10003 * 0.8F);
         var4.flareCol.setTo(this.color);
         var4.flareCol.scale(var5);
         var4.flareCol.getExterior().a = 1.0F;
         var4.flareCol.getInterior().a = 1.0F;
         var4.outColor.getExterior().r = var4.outColor.getExterior().r > var4.flareCol.getExterior().r
            ? var4.outColor.getExterior().r
            : var4.flareCol.getExterior().r;
         var4.outColor.getExterior().g = var4.outColor.getExterior().g > var4.flareCol.getExterior().g
            ? var4.outColor.getExterior().g
            : var4.flareCol.getExterior().g;
         var4.outColor.getExterior().b = var4.outColor.getExterior().b > var4.flareCol.getExterior().b
            ? var4.outColor.getExterior().b
            : var4.flareCol.getExterior().b;
         var4.outColor.getExterior().a = var4.outColor.getExterior().a > var4.flareCol.getExterior().a
            ? var4.outColor.getExterior().a
            : var4.flareCol.getExterior().a;
         var4.outColor.getInterior().r = var4.outColor.getInterior().r > var4.flareCol.getInterior().r
            ? var4.outColor.getInterior().r
            : var4.flareCol.getInterior().r;
         var4.outColor.getInterior().g = var4.outColor.getInterior().g > var4.flareCol.getInterior().g
            ? var4.outColor.getInterior().g
            : var4.flareCol.getInterior().g;
         var4.outColor.getInterior().b = var4.outColor.getInterior().b > var4.flareCol.getInterior().b
            ? var4.outColor.getInterior().b
            : var4.flareCol.getInterior().b;
         var4.outColor.getInterior().a = var4.outColor.getInterior().a > var4.flareCol.getInterior().a
            ? var4.outColor.getInterior().a
            : var4.flareCol.getInterior().a;
    float var8 = 1.0F - var6 * var4.intensity;
         var4.outColor.interp(var7, var8, var7);
    float var9 = ClimateManager.lerp(var8, 0.35F, var1.CM_Ambient);
         var1.CM_Ambient = var1.CM_Ambient > var9 ? var1.CM_Ambient : var9;
    float var10 = ClimateManager.lerp(var8, 0.6F * var4.intensity, var1.CM_DayLightStrength);
         var1.CM_DayLightStrength = var1.CM_DayLightStrength > var10 ? var1.CM_DayLightStrength : var10;
         if (Core.getInstance().RenderShader != nullptr && Core.getInstance().getOffscreenBuffer() != nullptr) {
    float var11 = ClimateManager.lerp(var8, 1.0F * var5, var1.CM_Desaturation);
            var1.CM_Desaturation = var1.CM_Desaturation > var11 ? var1.CM_Desaturation : var11;
         }
      }
   }
}
} // namespace weather
} // namespace iso
} // namespace zombie
