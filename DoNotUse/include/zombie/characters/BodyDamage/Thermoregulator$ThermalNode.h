#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characterTextures/BloodBodyPartType.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/skinnedmodel/visual/ItemVisual.h"
#include "zombie/inventory/types/Clothing.h"
#include "zombie/iso/weather/Temperature.h"

namespace zombie {
namespace characters {
namespace BodyDamage {


class Thermoregulator {
public:
    const float distToCore;
    const float skinSurface;
    const BodyPartType bodyPartType;
    const BloodBodyPartType bloodBPT;
    const BodyPart bodyPart;
    const bool isCore;
    const float insulationLayerMultiplierUI;
   private Thermoregulator$ThermalNode upstream;
   private Thermoregulator$ThermalNode[] downstream;
    float insulation;
    float windresist;
    float celcius;
    float skinCelcius;
    float heatDelta;
    float primaryDelta;
    float secondaryDelta;
    float clothingWetness;
    float bodyWetness;
   private std::vector<Clothing> clothing;

   public Thermoregulator$ThermalNode(Thermoregulator var1, float var2, BodyPart var3, float var4) {
      this(var1, false, var2, var3, var4);
   }

   public Thermoregulator$ThermalNode(Thermoregulator var1, boolean var2, float var3, BodyPart var4, float var5) {
      this.this$0 = var1;
      this.celcius = 37.0F;
      this.skinCelcius = 33.0F;
      this.heatDelta = 0.0F;
      this.primaryDelta = 0.0F;
      this.secondaryDelta = 0.0F;
      this.clothingWetness = 0.0F;
      this.bodyWetness = 0.0F;
      this.clothing = std::make_unique<std::vector<>>();
      this.isCore = var2;
      this.celcius = var3;
      this.distToCore = BodyPartType.GetDistToCore(var4.Type);
      this.skinSurface = BodyPartType.GetSkinSurface(var4.Type);
      this.bodyPartType = var4.Type;
      this.bloodBPT = BloodBodyPartType.FromIndex(BodyPartType.ToIndex(var4.Type));
      this.bodyPart = var4;
      this.insulationLayerMultiplierUI = var5;
   }

    void calculateInsulation() {
    int var1 = this.clothing.size();
      this.insulation = 0.0F;
      this.windresist = 0.0F;
      this.clothingWetness = 0.0F;
      this.bodyWetness = this.bodyPart != nullptr ? this.bodyPart.getWetness() * 0.01F : 0.0F;
      this.bodyWetness = PZMath.clamp_01(this.bodyWetness);
      if (var1 > 0) {
         for (int var4 = 0; var4 < var1; var4++) {
    Clothing var2 = this.clothing.get(var4);
    ItemVisual var3 = var2.getVisual();
    float var5 = PZMath.clamp(var2.getWetness() * 0.01F, 0.0F, 1.0F);
            this.clothingWetness += var5;
    bool var6 = var3.getHole(this.bloodBPT) > 0.0F;
            if (!var6) {
    float var7 = Temperature.getTrueInsulationValue(var2.getInsulation());
    float var8 = Temperature.getTrueWindresistanceValue(var2.getWindresistance());
    float var9 = PZMath.clamp(var2.getCurrentCondition() * 0.01F, 0.0F, 1.0F);
               var9 = 0.5F + 0.5F * var9;
               var7 *= (1.0F - var5 * 0.75F) * var9;
               var8 *= (1.0F - var5 * 0.45F) * var9;
               this.insulation += var7;
               this.windresist += var8;
            }
         }

         this.clothingWetness /= var1;
         this.insulation += var1 * 0.05F;
         this.windresist += var1 * 0.05F;
      }
   }

    std::string getName() {
      return this.bodyPartType;
   }

    bool hasUpstream() {
      return this.upstream != nullptr;
   }

    bool hasDownstream() {
      return this.downstream != nullptr && this.downstream.length > 0;
   }

    float getDistToCore() {
      return this.distToCore;
   }

    float getSkinSurface() {
      return this.skinSurface;
   }

    bool isCore() {
      return this.isCore;
   }

    float getInsulation() {
      return this.insulation;
   }

    float getWindresist() {
      return this.windresist;
   }

    float getCelcius() {
      return this.celcius;
   }

    float getSkinCelcius() {
      return this.skinCelcius;
   }

    float getHeatDelta() {
      return this.heatDelta;
   }

    float getPrimaryDelta() {
      return this.primaryDelta;
   }

    float getSecondaryDelta() {
      return this.secondaryDelta;
   }

    float getClothingWetness() {
      return this.clothingWetness;
   }

    float getBodyWetness() {
      return this.bodyWetness;
   }

    float getBodyResponse() {
      return PZMath.lerp(this.primaryDelta, this.secondaryDelta, 0.5F);
   }

    float getSkinCelciusUI() {
    float var1 = PZMath.clamp(this.getSkinCelcius(), 20.0F, 42.0F);
      if (var1 < 33.0F) {
         var1 = (var1 - 20.0F) / 13.0F * 0.5F;
      } else {
         var1 = 0.5F + (var1 - 33.0F) / 9.0F;
      }

    return var1;
   }

    float getHeatDeltaUI() {
      return PZMath.clamp((this.heatDelta * 0.2F + 1.0F) / 2.0F, 0.0F, 1.0F);
   }

    float getPrimaryDeltaUI() {
      return PZMath.clamp((this.primaryDelta + 1.0F) / 2.0F, 0.0F, 1.0F);
   }

    float getSecondaryDeltaUI() {
      return PZMath.clamp((this.secondaryDelta + 1.0F) / 2.0F, 0.0F, 1.0F);
   }

    float getInsulationUI() {
      return PZMath.clamp(this.insulation * this.insulationLayerMultiplierUI, 0.0F, 1.0F);
   }

    float getWindresistUI() {
      return PZMath.clamp(this.windresist * this.insulationLayerMultiplierUI, 0.0F, 1.0F);
   }

    float getClothingWetnessUI() {
      return PZMath.clamp(this.clothingWetness, 0.0F, 1.0F);
   }

    float getBodyWetnessUI() {
      return PZMath.clamp(this.bodyWetness, 0.0F, 1.0F);
   }

    float getBodyResponseUI() {
      return PZMath.clamp((this.getBodyResponse() + 1.0F) / 2.0F, 0.0F, 1.0F);
   }
}
} // namespace BodyDamage
} // namespace characters
} // namespace zombie
