#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Vector3f.h"
#include "org/lwjgl/opengl/GL.h"
#include "zombie/GameTime.h"
#include "zombie/core/Color.h"
#include "zombie/core/Core.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/core/opengl/Shader.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/core/textures/TextureFBO.h"
#include "zombie/core/utils/UpdateLimit.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/interfaces/ITexture.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/weather/ClimateManager.h"
#include "zombie/iso/weather/ClimateManager/DayInfo.h"

namespace zombie {
namespace iso {
namespace sprite {


class SkyBox : public IsoObject {
public:
    static SkyBox instance;
    IsoSpriteInstance def = nullptr;
    TextureFBO textureFBOA;
    TextureFBO textureFBOB;
    bool isCurrentA;
    Shader Effect;
    const UpdateLimit renderLimit = std::make_shared<UpdateLimit>(1000L);
    bool isUpdated = false;
    int SkyBoxTime;
    float SkyBoxParamCloudCount;
    float SkyBoxParamCloudSize;
    const Vector3f SkyBoxParamSunLight = std::make_shared<Vector3f>();
    const Color SkyBoxParamSunColor = std::make_shared<Color>(1.0F, 1.0F, 1.0F);
    const Color SkyBoxParamSkyHColour = std::make_shared<Color>(1.0F, 1.0F, 1.0F);
    const Color SkyBoxParamSkyLColour = std::make_shared<Color>(1.0F, 1.0F, 1.0F);
    float SkyBoxParamCloudLight;
    float SkyBoxParamStars;
    float SkyBoxParamFog;
    const Vector3f SkyBoxParamWind;
    bool isSetAVG = false;
    float SkyBoxParamCloudCountAVG;
    float SkyBoxParamCloudSizeAVG;
    const Vector3f SkyBoxParamSunLightAVG = std::make_shared<Vector3f>();
    const Color SkyBoxParamSunColorAVG = std::make_shared<Color>(1.0F, 1.0F, 1.0F);
    const Color SkyBoxParamSkyHColourAVG = std::make_shared<Color>(1.0F, 1.0F, 1.0F);
    const Color SkyBoxParamSkyLColourAVG = std::make_shared<Color>(1.0F, 1.0F, 1.0F);
    float SkyBoxParamCloudLightAVG;
    float SkyBoxParamStarsAVG;
    float SkyBoxParamFogAVG;
    const Vector3f SkyBoxParamWindINT;
    Texture texAM;
    Texture texPM;
    const Color SkyHColourDay = std::make_shared<Color>(0.1F, 0.1F, 0.4F);
    const Color SkyHColourDawn = std::make_shared<Color>(0.2F, 0.2F, 0.3F);
    const Color SkyHColourDusk = std::make_shared<Color>(0.2F, 0.2F, 0.3F);
    const Color SkyHColourNight = std::make_shared<Color>(0.01F, 0.01F, 0.04F);
    const Color SkyLColourDay = std::make_shared<Color>(0.1F, 0.45F, 0.7F);
    const Color SkyLColourDawn = std::make_shared<Color>(0.1F, 0.4F, 0.6F);
    const Color SkyLColourDusk = std::make_shared<Color>(0.1F, 0.4F, 0.6F);
    const Color SkyLColourNight = std::make_shared<Color>(0.01F, 0.045F, 0.07F);
    int apiId;

   public static /* synchronized - TODO: add std::mutex */ SkyBox getInstance() {
      if (instance == nullptr) {
         instance = std::make_unique<SkyBox>();
      }

    return instance;
   }

    void update(ClimateManager var1) {
      if (!this.isUpdated) {
         this.isUpdated = true;
    GameTime var2 = GameTime.getInstance();
    DayInfo var3 = var1.getCurrentDay();
    float var4 = var3.season.getDawn();
    float var5 = var3.season.getDusk();
    float var6 = var3.season.getDayHighNoon();
    float var7 = var2.getTimeOfDay();
         if (var7 < var4 || var7 > var5) {
    float var11 = 24.0F - var5 + var4;
            if (var7 > var5) {
    float var9 = (var7 - var5) / var11;
               this.SkyHColourDusk.interp(this.SkyHColourDawn, var9, this.SkyBoxParamSkyHColour);
               this.SkyLColourDusk.interp(this.SkyLColourDawn, var9, this.SkyBoxParamSkyLColour);
               this.SkyBoxParamSunLight.set(0.35F, 0.22F, 0.3F);
               this.SkyBoxParamSunLight.normalize();
               this.SkyBoxParamSunLight.mul(Math.min(1.0F, var9 * 5.0F));
            } else {
    float var14 = (24.0F - var5 + var7) / var11;
               this.SkyHColourDusk.interp(this.SkyHColourDawn, var14, this.SkyBoxParamSkyHColour);
               this.SkyLColourDusk.interp(this.SkyLColourDawn, var14, this.SkyBoxParamSkyLColour);
               this.SkyBoxParamSunLight.set(0.35F, 0.22F, 0.3F);
               this.SkyBoxParamSunLight.normalize();
               this.SkyBoxParamSunLight.mul(Math.min(1.0F, (1.0F - var14) * 5.0F));
            }

            this.SkyBoxParamSunColor.set(var1.getGlobalLight().getExterior());
            this.SkyBoxParamSunColor.scale(var1.getNightStrength());
         } else if (var7 < var6) {
    float var8 = (var7 - var4) / (var6 - var4);
            this.SkyHColourDawn.interp(this.SkyHColourDay, var8, this.SkyBoxParamSkyHColour);
            this.SkyLColourDawn.interp(this.SkyLColourDay, var8, this.SkyBoxParamSkyLColour);
            this.SkyBoxParamSunLight.set(4.0F * var8 - 4.0F, 0.22F, 0.3F);
            this.SkyBoxParamSunLight.normalize();
            this.SkyBoxParamSunLight.mul(Math.min(1.0F, var8 * 10.0F));
            this.SkyBoxParamSunColor.set(var1.getGlobalLight().getExterior());
         } else {
    float var10 = (var7 - var6) / (var5 - var6);
            this.SkyHColourDay.interp(this.SkyHColourDusk, var10, this.SkyBoxParamSkyHColour);
            this.SkyLColourDay.interp(this.SkyLColourDusk, var10, this.SkyBoxParamSkyLColour);
            this.SkyBoxParamSunLight.set(4.0F * var10, 0.22F, 0.3F);
            this.SkyBoxParamSunLight.normalize();
            this.SkyBoxParamSunLight.mul(Math.min(1.0F, (1.0F - var10) * 10.0F));
            this.SkyBoxParamSunColor.set(var1.getGlobalLight().getExterior());
         }

         this.SkyBoxParamSkyHColour.interp(this.SkyHColourNight, var1.getNightStrength(), this.SkyBoxParamSkyHColour);
         this.SkyBoxParamSkyLColour.interp(this.SkyLColourNight, var1.getNightStrength(), this.SkyBoxParamSkyLColour);
         this.SkyBoxParamCloudCount = Math.min(Math.max(var1.getCloudIntensity(), var1.getPrecipitationIntensity() * 2.0F), 0.999F);
         this.SkyBoxParamCloudSize = 0.02F + var1.getTemperature() / 70.0F;
         this.SkyBoxParamFog = var1.getFogIntensity();
         this.SkyBoxParamStars = var1.getNightStrength();
         this.SkyBoxParamCloudLight = (float)(1.0 - (1.0 - 1.0 * Math.pow(1000.0, -var1.getPrecipitationIntensity() - var1.getNightStrength())));
    float var12 = (1.0F - (var1.getWindAngleIntensity() + 1.0F) * 0.5F + 0.25F) % 1.0F;
         var12 *= 360.0F;
         this.SkyBoxParamWind.set((float)Math.cos(Math.toRadians(var12)), 0.0F, (float)Math.sin(Math.toRadians(var12)));
         this.SkyBoxParamWind.mul(var1.getWindIntensity());
         if (!this.isSetAVG) {
            this.isSetAVG = true;
            this.SkyBoxParamCloudCountAVG = this.SkyBoxParamCloudCount;
            this.SkyBoxParamCloudSizeAVG = this.SkyBoxParamCloudSize;
            this.SkyBoxParamSunLightAVG.set(this.SkyBoxParamSunLight);
            this.SkyBoxParamSunColorAVG.set(this.SkyBoxParamSunColor);
            this.SkyBoxParamSkyHColourAVG.set(this.SkyBoxParamSkyHColour);
            this.SkyBoxParamSkyLColourAVG.set(this.SkyBoxParamSkyLColour);
            this.SkyBoxParamCloudLightAVG = this.SkyBoxParamCloudLight;
            this.SkyBoxParamStarsAVG = this.SkyBoxParamStars;
            this.SkyBoxParamFogAVG = this.SkyBoxParamFog;
            this.SkyBoxParamWindINT.set(this.SkyBoxParamWind);
         } else {
            this.SkyBoxParamCloudCountAVG = this.SkyBoxParamCloudCountAVG + (this.SkyBoxParamCloudCount - this.SkyBoxParamCloudCountAVG) * 0.1F;
            this.SkyBoxParamCloudSizeAVG = this.SkyBoxParamCloudSizeAVG + (this.SkyBoxParamCloudSizeAVG + this.SkyBoxParamCloudSize) * 0.1F;
            this.SkyBoxParamSunLightAVG.lerp(this.SkyBoxParamSunLight, 0.1F);
            this.SkyBoxParamSunColorAVG.interp(this.SkyBoxParamSunColor, 0.1F, this.SkyBoxParamSunColorAVG);
            this.SkyBoxParamSkyHColourAVG.interp(this.SkyBoxParamSkyHColour, 0.1F, this.SkyBoxParamSkyHColourAVG);
            this.SkyBoxParamSkyLColourAVG.interp(this.SkyBoxParamSkyLColour, 0.1F, this.SkyBoxParamSkyLColourAVG);
            this.SkyBoxParamCloudLightAVG = this.SkyBoxParamCloudLightAVG + (this.SkyBoxParamCloudLight - this.SkyBoxParamCloudLightAVG) * 0.1F;
            this.SkyBoxParamStarsAVG = this.SkyBoxParamStarsAVG + (this.SkyBoxParamStars - this.SkyBoxParamStarsAVG) * 0.1F;
            this.SkyBoxParamFogAVG = this.SkyBoxParamFogAVG + (this.SkyBoxParamFog - this.SkyBoxParamFogAVG) * 0.1F;
            this.SkyBoxParamWindINT.push_back(this.SkyBoxParamWind);
         }
      }
   }

    int getShaderTime() {
      return this.SkyBoxTime;
   }

    float getShaderCloudCount() {
      return this.SkyBoxParamCloudCount;
   }

    float getShaderCloudSize() {
      return this.SkyBoxParamCloudSize;
   }

    Vector3f getShaderSunLight() {
      return this.SkyBoxParamSunLight;
   }

    Color getShaderSunColor() {
      return this.SkyBoxParamSunColor;
   }

    Color getShaderSkyHColour() {
      return this.SkyBoxParamSkyHColour;
   }

    Color getShaderSkyLColour() {
      return this.SkyBoxParamSkyLColour;
   }

    float getShaderCloudLight() {
      return this.SkyBoxParamCloudLight;
   }

    float getShaderStars() {
      return this.SkyBoxParamStars;
   }

    float getShaderFog() {
      return this.SkyBoxParamFog;
   }

    Vector3f getShaderWind() {
      return this.SkyBoxParamWindINT;
   }

    public SkyBox() {
      this.texAM = Texture.getSharedTexture("media/textures/CMVehicleReflection/ref_am.png");
      this.texPM = Texture.getSharedTexture("media/textures/CMVehicleReflection/ref_am.png");

      try {
    Texture var1 = std::make_shared<Texture>(512, 512, 16);
    Texture var2 = std::make_shared<Texture>(512, 512, 16);
         this.textureFBOA = std::make_shared<TextureFBO>(var1);
         this.textureFBOB = std::make_shared<TextureFBO>(var2);
      } catch (Exception var3) {
         var3.printStackTrace();
      }

      this.def = IsoSpriteInstance.get(this.sprite);
      this.SkyBoxTime = 0;
      this.SkyBoxParamSunLight.set(0.35F, 0.22F, 0.3F);
      this.SkyBoxParamSunColor.set(1.0F, 0.86F, 0.7F, 1.0F);
      this.SkyBoxParamSkyHColour.set(0.1F, 0.1F, 0.4F, 1.0F);
      this.SkyBoxParamSkyLColour.set(0.1F, 0.45F, 0.7F, 1.0F);
      this.SkyBoxParamCloudLight = 0.99F;
      this.SkyBoxParamCloudCount = 0.3F;
      this.SkyBoxParamCloudSize = 0.2F;
      this.SkyBoxParamFog = 0.0F;
      this.SkyBoxParamStars = 0.0F;
      this.SkyBoxParamWind = std::make_shared<Vector3f>(0.0F);
      this.SkyBoxParamWindINT = std::make_shared<Vector3f>(0.0F);
      RenderThread.invokeOnRenderContext(() -> {
         if (Core.getInstance().getPerfSkybox() == 0) {
            this.Effect = std::make_shared<SkyBoxShader>("skybox_hires");
         } else {
            this.Effect = std::make_shared<SkyBoxShader>("skybox");
         }

         if (GL.getCapabilities().OpenGL30) {
            this.apiId = 1;
         }

         if (GL.getCapabilities().GL_ARB_framebuffer_object) {
            this.apiId = 2;
         }

         if (GL.getCapabilities().GL_EXT_framebuffer_object) {
            this.apiId = 3;
         }
      });
   }

    ITexture getTextureCurrent() {
      if (!Core.getInstance().getUseShaders() || Core.getInstance().getPerfSkybox() == 2) {
         return this.texAM;
      } else {
         return this.isCurrentA ? this.textureFBOA.getTexture() : this.textureFBOB.getTexture();
      }
   }

    ITexture getTexturePrev() {
      if (!Core.getInstance().getUseShaders() || Core.getInstance().getPerfSkybox() == 2) {
         return this.texPM;
      } else {
         return this.isCurrentA ? this.textureFBOB.getTexture() : this.textureFBOA.getTexture();
      }
   }

    TextureFBO getTextureFBOPrev() {
      if (!Core.getInstance().getUseShaders() || Core.getInstance().getPerfSkybox() == 2) {
    return nullptr;
      } else {
         return this.isCurrentA ? this.textureFBOB : this.textureFBOA;
      }
   }

    float getTextureShift() {
      return Core.getInstance().getUseShaders() && Core.getInstance().getPerfSkybox() != 2
         ? (float)this.renderLimit.getTimePeriod()
         : 1.0F - GameTime.getInstance().getNight();
   }

    void swapTextureFBO() {
      this.renderLimit.updateTimePeriod();
      this.isCurrentA = !this.isCurrentA;
   }

    void render() {
      if (Core.getInstance().getUseShaders() && Core.getInstance().getPerfSkybox() != 2) {
         if (!this.renderLimit.Check()) {
            if (GameTime.getInstance().getMultiplier() >= 20.0F) {
               this.SkyBoxTime++;
            }
         } else {
            this.SkyBoxTime++;
    int var1 = IsoCamera.frameState.playerIndex;
    int var2 = IsoCamera.getOffscreenLeft(var1);
    int var3 = IsoCamera.getOffscreenTop(var1);
    int var4 = IsoCamera.getOffscreenWidth(var1);
    int var5 = IsoCamera.getOffscreenHeight(var1);
            SpriteRenderer.instance.drawSkyBox(this.Effect, var1, this.apiId, this.getTextureFBOPrev().getBufferId());
            this.isUpdated = false;
         }
      }
   }

    void draw() {
      if (Core.bDebug && DebugOptions.instance.SkyboxShow.getValue()) {
         ((Texture)this.getTextureCurrent()).render(0.0F, 0.0F, 512.0F, 512.0F, 1.0F, 1.0F, 1.0F, 1.0F, nullptr);
      }
   }
}
} // namespace sprite
} // namespace iso
} // namespace zombie
