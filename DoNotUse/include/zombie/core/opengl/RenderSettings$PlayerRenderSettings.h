#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/IndieGL.h"
#include "zombie/SandboxOptions.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Color.h"
#include "zombie/core/Core.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/SearchMode.h"
#include "zombie/iso/weather/ClimateColorInfo.h"
#include "zombie/iso/weather/ClimateManager.h"
#include "zombie/iso/weather/ClimateMoon.h"
#include "zombie/iso/weather/WorldFlares.h"

namespace zombie {
namespace core {
namespace opengl {


class RenderSettings {
public:
    ClimateColorInfo CM_GlobalLight = std::make_shared<ClimateColorInfo>();
    float CM_NightStrength = 0.0F;
    float CM_Desaturation = 0.0F;
    float CM_GlobalLightIntensity = 0.0F;
    float CM_Ambient = 0.0F;
    float CM_ViewDistance = 0.0F;
    float CM_DayLightStrength = 0.0F;
    float CM_FogIntensity = 0.0F;
    Color blendColor = std::make_shared<Color>(1.0F, 1.0F, 1.0F, 1.0F);
    ColorInfo blendInfo = std::make_shared<ColorInfo>();
    float blendIntensity = 0.0F;
    float desaturation = 0.0F;
    float darkness = 0.0F;
    float night = 0.0F;
    float viewDistance = 0.0F;
    float ambient = 0.0F;
    bool applyNightVisionGoggles = false;
    float goggleMod = 0.0F;
    bool isExterior = false;
    float fogMod = 1.0F;
    float rmod;
    float gmod;
    float bmod;
    float SM_Radius = 0.0F;
    float SM_Alpha = 0.0F;
    Color maskClearColor = std::make_shared<Color>(0, 0, 0, 1);

    void updateRenderSettings(int var1, IsoPlayer var2) {
    SearchMode var3 = SearchMode.getInstance();
      this.SM_Alpha = 0.0F;
      this.SM_Radius = 0.0F;
    ClimateManager var4 = ClimateManager.getInstance();
      this.CM_GlobalLight = var4.getGlobalLight();
      this.CM_GlobalLightIntensity = var4.getGlobalLightIntensity();
      this.CM_Ambient = var4.getAmbient();
      this.CM_DayLightStrength = var4.getDayLightStrength();
      this.CM_NightStrength = var4.getNightStrength();
      this.CM_Desaturation = var4.getDesaturation();
      this.CM_ViewDistance = var4.getViewDistance();
      this.CM_FogIntensity = var4.getFogIntensity();
      var4.getThunderStorm().applyLightningForPlayer(this, var1, var2);
      WorldFlares.applyFlaresForPlayer(this, var1, var2);
    int var5 = SandboxOptions.instance.NightDarkness.getValue();
      this.desaturation = this.CM_Desaturation;
      this.viewDistance = this.CM_ViewDistance;
      this.applyNightVisionGoggles = var2 != nullptr && var2.isWearingNightVisionGoggles();
      this.isExterior = var2 != nullptr && (var2.isDead() || var2.getCurrentSquare() != nullptr && !var2.getCurrentSquare().isInARoom());
      this.fogMod = 1.0F - this.CM_FogIntensity * 0.5F;
      this.night = this.CM_NightStrength;
      this.darkness = 1.0F - this.CM_DayLightStrength;
      if (this.isExterior) {
         this.setBlendColor(this.CM_GlobalLight.getExterior());
         this.blendIntensity = this.CM_GlobalLight.getExterior().a;
      } else {
         this.setBlendColor(this.CM_GlobalLight.getInterior());
         this.blendIntensity = this.CM_GlobalLight.getInterior().a;
      }

      this.ambient = this.CM_Ambient;
      this.viewDistance = this.CM_ViewDistance;
    float var6 = 0.2F + 0.1F * --var5;
      var6 += 0.075F * ClimateMoon.getMoonFloat() * this.night;
      if (!this.isExterior) {
         var6 *= 0.925F - 0.075F * this.darkness;
         this.desaturation *= 0.25F;
      }

      if (this.ambient < 0.2F && var2.getCharacterTraits().NightVision.isSet()) {
         this.ambient = 0.2F;
      }

      this.ambient = var6 + (1.0F - var6) * this.ambient;
      if (Core.bLastStand) {
         this.ambient = 0.65F;
         this.darkness = 0.25F;
         this.night = 0.25F;
      }

      if (Core.getInstance().RenderShader == nullptr || Core.getInstance().getOffscreenBuffer() == nullptr) {
         this.desaturation = this.desaturation * (1.0F - this.darkness);
         this.blendInfo.r = this.blendColor.r;
         this.blendInfo.g = this.blendColor.g;
         this.blendInfo.b = this.blendColor.b;
         this.blendInfo.desaturate(this.desaturation);
         this.rmod = GameTime.getInstance().Lerp(1.0F, this.blendInfo.r, this.blendIntensity);
         this.gmod = GameTime.getInstance().Lerp(1.0F, this.blendInfo.g, this.blendIntensity);
         this.bmod = GameTime.getInstance().Lerp(1.0F, this.blendInfo.b, this.blendIntensity);
         if (this.applyNightVisionGoggles) {
            this.goggleMod = 1.0F - 0.9F * this.darkness;
            this.blendIntensity = 0.0F;
            this.night = 0.0F;
            this.ambient = 0.8F;
            this.rmod = 1.0F;
            this.gmod = 1.0F;
            this.bmod = 1.0F;
         }
      } else if (this.applyNightVisionGoggles) {
         this.ambient = 1.0F;
         this.rmod = GameTime.getInstance().Lerp(1.0F, 0.7F, this.darkness);
         this.gmod = GameTime.getInstance().Lerp(1.0F, 0.7F, this.darkness);
         this.bmod = GameTime.getInstance().Lerp(1.0F, 0.7F, this.darkness);
         this.maskClearColor.r = 0.0F;
         this.maskClearColor.g = 0.0F;
         this.maskClearColor.b = 0.0F;
         this.maskClearColor.a = 0.0F;
      } else {
         this.rmod = 1.0F;
         this.gmod = 1.0F;
         this.bmod = 1.0F;
         if (!this.isExterior) {
            this.maskClearColor.r = this.CM_GlobalLight.getInterior().r;
            this.maskClearColor.g = this.CM_GlobalLight.getInterior().g;
            this.maskClearColor.b = this.CM_GlobalLight.getInterior().b;
            this.maskClearColor.a = this.CM_GlobalLight.getInterior().a;
         } else {
            this.maskClearColor.r = 0.0F;
            this.maskClearColor.g = 0.0F;
            this.maskClearColor.b = 0.0F;
            this.maskClearColor.a = 0.0F;
         }
      }
   }

    void applyRenderSettings(int var1) {
      IsoGridSquare.rmod = this.rmod;
      IsoGridSquare.gmod = this.gmod;
      IsoGridSquare.bmod = this.bmod;
      IsoObject.rmod = this.rmod;
      IsoObject.gmod = this.gmod;
      IsoObject.bmod = this.bmod;
   }

    void legacyPostRender(int var1) {
      SpriteRenderer.instance.glIgnoreStyles(true);
      if (this.applyNightVisionGoggles) {
         IndieGL.glBlendFunc(770, 768);
         SpriteRenderer.instance
            .render(
               RenderSettings.texture,
               0.0F,
               0.0F,
               Core.getInstance().getOffscreenWidth(var1),
               Core.getInstance().getOffscreenHeight(var1),
               0.05F,
               0.95F,
               0.05F,
               this.goggleMod,
               nullptr
            );
         IndieGL.glBlendFunc(770, 771);
      } else {
         IndieGL.glBlendFunc(774, 774);
         SpriteRenderer.instance
            .render(
               RenderSettings.texture,
               0.0F,
               0.0F,
               Core.getInstance().getOffscreenWidth(var1),
               Core.getInstance().getOffscreenHeight(var1),
               this.blendInfo.r,
               this.blendInfo.g,
               this.blendInfo.b,
               1.0F,
               nullptr
            );
         IndieGL.glBlendFunc(770, 771);
      }

      SpriteRenderer.instance.glIgnoreStyles(false);
   }

    Color getBlendColor() {
      return this.blendColor;
   }

    float getBlendIntensity() {
      return this.blendIntensity;
   }

    float getDesaturation() {
      return this.desaturation;
   }

    float getDarkness() {
      return this.darkness;
   }

    float getNight() {
      return this.night;
   }

    float getViewDistance() {
      return this.viewDistance;
   }

    float getAmbient() {
      return this.ambient;
   }

    bool isApplyNightVisionGoggles() {
      return this.applyNightVisionGoggles;
   }

    float getRmod() {
      return this.rmod;
   }

    float getGmod() {
      return this.gmod;
   }

    float getBmod() {
      return this.bmod;
   }

    bool isExterior() {
      return this.isExterior;
   }

    float getFogMod() {
      return this.fogMod;
   }

    void setBlendColor(Color var1) {
      this.blendColor.a = var1.a;
      this.blendColor.r = var1.r;
      this.blendColor.g = var1.g;
      this.blendColor.b = var1.b;
   }

    Color getMaskClearColor() {
      return this.maskClearColor;
   }

    float getSM_Radius() {
      return this.SM_Radius;
   }

    float getSM_Alpha() {
      return this.SM_Alpha;
   }
}
} // namespace opengl
} // namespace core
} // namespace zombie
