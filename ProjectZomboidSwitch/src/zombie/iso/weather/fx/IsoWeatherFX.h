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
#include "zombie/core/PerformanceSettings.h"
#include "zombie/core/Rand.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/core/skinnedmodel/shader/Shader.h"
#include "zombie/core/skinnedmodel/shader/ShaderManager.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/weather/ClimateManager.h"
#include "zombie/iso/weather/fx/IsoWeatherFX/Drawer.h"
#include "zombie/network/GameServer.h"

namespace zombie {
namespace iso {
namespace weather {
namespace fx {


class IsoWeatherFX {
public:
    static bool VERBOSE = false;
    static bool DEBUG_BOUNDS = false;
    static float DELTA;
    ParticleRectangle cloudParticles;
    ParticleRectangle fogParticles;
    ParticleRectangle snowParticles;
    ParticleRectangle rainParticles;
    static int ID_CLOUD = 0;
    static int ID_FOG = 1;
    static int ID_SNOW = 2;
    static int ID_RAIN = 3;
    static float ZoomMod = 1.0F;
    bool playerIndoors = false;
    SteppedUpdateFloat windPrecipIntensity = std::make_shared<SteppedUpdateFloat>(0.0F, 0.025F, 0.0F, 1.0F);
    SteppedUpdateFloat windIntensity = std::make_shared<SteppedUpdateFloat>(0.0F, 0.005F, 0.0F, 1.0F);
    SteppedUpdateFloat windAngleIntensity = std::make_shared<SteppedUpdateFloat>(0.0F, 0.005F, -1.0F, 1.0F);
    SteppedUpdateFloat precipitationIntensity = std::make_shared<SteppedUpdateFloat>(0.0F, 0.005F, 0.0F, 1.0F);
    SteppedUpdateFloat precipitationIntensitySnow = std::make_shared<SteppedUpdateFloat>(0.0F, 0.005F, 0.0F, 1.0F);
    SteppedUpdateFloat precipitationIntensityRain = std::make_shared<SteppedUpdateFloat>(0.0F, 0.005F, 0.0F, 1.0F);
    SteppedUpdateFloat cloudIntensity = std::make_shared<SteppedUpdateFloat>(0.0F, 0.005F, 0.0F, 1.0F);
    SteppedUpdateFloat fogIntensity = std::make_shared<SteppedUpdateFloat>(0.0F, 0.005F, 0.0F, 1.0F);
    SteppedUpdateFloat windAngleMod = std::make_shared<SteppedUpdateFloat>(0.0F, 0.005F, 0.0F, 1.0F);
    bool precipitationIsSnow = true;
    float fogOverlayAlpha = 0.0F;
    float windSpeedMax = 6.0F;
    float windSpeed = 0.0F;
    float windSpeedFog = 0.0F;
    float windAngle = 90.0F;
    float windAngleClouds = 90.0F;
    Texture texFogCircle;
    Texture texFogWhite;
    Color fogColor = std::make_shared<Color>(1.0F, 1.0F, 1.0F, 1.0F);
    SteppedUpdateFloat indoorsAlphaMod = std::make_shared<SteppedUpdateFloat>(1.0F, 0.05F, 0.0F, 1.0F);
   private std::vector<ParticleRectangle> particleRectangles = new std::vector<>(0);
    static IsoWeatherFX instance;
    float windUpdCounter = 0.0F;
    static Shader s_shader;
   static const Drawer[][] s_drawer = new Drawer[4][3];

    public IsoWeatherFX() {
      instance = this;
   }

    void init() {
      if (!GameServer.bServer) {
    int var1 = 0;
         Texture[] var2 = new Texture[6];

         for (int var3 = 0; var3 < var2.length; var3++) {
            var2[var3] = Texture.getSharedTexture("media/textures/weather/clouds_" + var3 + ".png");
            if (var2[var3] == nullptr) {
               DebugLog.log("Missing texture: media/textures/weather/clouds_" + var3 + ".png");
            }
         }

         this.cloudParticles = std::make_shared<ParticleRectangle>(8192, 4096);
         WeatherParticle[] var15 = new WeatherParticle[16];

         for (int var4 = 0; var4 < var15.length; var4++) {
    Texture var5 = var2[Rand.Next(var2.length)];
    CloudParticle var6 = std::make_shared<CloudParticle>(var5, var5.getWidth() * 8, var5.getHeight() * 8);
            var6.position.set(Rand.Next(0, this.cloudParticles.getWidth()), Rand.Next(0, this.cloudParticles.getHeight()));
            var6.speed = Rand.Next(0.01F, 0.1F);
            var6.angleOffset = 180.0F - Rand.Next(0.0F, 360.0F);
            var6.alpha = Rand.Next(0.25F, 0.75F);
            var15[var4] = var6;
         }

         this.cloudParticles.SetParticles(var15);
         this.cloudParticles.SetParticlesStrength(1.0F);
         this.particleRectangles.push_back(var1, this.cloudParticles);
         ID_CLOUD = var1++;
         if (this.texFogCircle == nullptr) {
            this.texFogCircle = Texture.getSharedTexture("media/textures/weather/fogcircle_tex.png", 35);
         }

         if (this.texFogWhite == nullptr) {
            this.texFogWhite = Texture.getSharedTexture("media/textures/weather/fogwhite_tex.png", 35);
         }

         Texture[] var16 = new Texture[6];

         for (int var17 = 0; var17 < var16.length; var17++) {
            var16[var17] = Texture.getSharedTexture("media/textures/weather/fog_" + var17 + ".png");
            if (var16[var17] == nullptr) {
               DebugLog.log("Missing texture: media/textures/weather/fog_" + var17 + ".png");
            }
         }

         this.fogParticles = std::make_shared<ParticleRectangle>(2048, 1024);
         WeatherParticle[] var18 = new WeatherParticle[16];

         for (int var19 = 0; var19 < var18.length; var19++) {
    Texture var7 = var16[Rand.Next(var16.length)];
    FogParticle var8 = std::make_shared<FogParticle>(var7, var7.getWidth() * 2, var7.getHeight() * 2);
            var8.position.set(Rand.Next(0, this.fogParticles.getWidth()), Rand.Next(0, this.fogParticles.getHeight()));
            var8.speed = Rand.Next(0.01F, 0.1F);
            var8.angleOffset = 180.0F - Rand.Next(0.0F, 360.0F);
            var8.alpha = Rand.Next(0.05F, 0.25F);
            var18[var19] = var8;
         }

         this.fogParticles.SetParticles(var18);
         this.fogParticles.SetParticlesStrength(1.0F);
         this.particleRectangles.push_back(var1, this.fogParticles);
         ID_FOG = var1++;
         Texture[] var20 = new Texture[3];

         for (int var21 = 0; var21 < var20.length; var21++) {
            var20[var21] = Texture.getSharedTexture("media/textures/weather/snow_" + (var21 + 1) + ".png");
            if (var20[var21] == nullptr) {
               DebugLog.log("Missing texture: media/textures/weather/snow_" + (var21 + 1) + ".png");
            }
         }

         this.snowParticles = std::make_shared<ParticleRectangle>(512, 512);
         WeatherParticle[] var22 = new WeatherParticle[1024];

         for (int var23 = 0; var23 < var22.length; var23++) {
    SnowParticle var9 = std::make_shared<SnowParticle>(var20[Rand.Next(var20.length)]);
            var9.position.set(Rand.Next(0, this.snowParticles.getWidth()), Rand.Next(0, this.snowParticles.getHeight()));
            var9.speed = Rand.Next(1.0F, 2.0F);
            var9.angleOffset = 15.0F - Rand.Next(0.0F, 30.0F);
            var9.alpha = Rand.Next(0.25F, 0.6F);
            var22[var23] = var9;
         }

         this.snowParticles.SetParticles(var22);
         this.particleRectangles.push_back(var1, this.snowParticles);
         ID_SNOW = var1++;
         this.rainParticles = std::make_shared<ParticleRectangle>(512, 512);
         WeatherParticle[] var24 = new WeatherParticle[1024];

         for (int var25 = 0; var25 < var24.length; var25++) {
    RainParticle var10 = std::make_shared<RainParticle>(this.texFogWhite, Rand.Next(5, 12));
            var10.position.set(Rand.Next(0, this.rainParticles.getWidth()), Rand.Next(0, this.rainParticles.getHeight()));
            var10.speed = Rand.Next(7, 12);
            var10.angleOffset = 3.0F - Rand.Next(0.0F, 6.0F);
            var10.alpha = Rand.Next(0.5F, 0.8F);
            var10.color = std::make_shared<Color>(Rand.Next(0.75F, 0.8F), Rand.Next(0.85F, 0.9F), Rand.Next(0.95F, 1.0F), 1.0F);
            var24[var25] = var10;
         }

         this.rainParticles.SetParticles(var24);
         this.particleRectangles.push_back(var1, this.rainParticles);
         ID_RAIN = var1++;
      }
   }

    void update() {
      if (!GameServer.bServer) {
         this.playerIndoors = IsoCamera.frameState.CamCharacterSquare != nullptr && !IsoCamera.frameState.CamCharacterSquare.Is(IsoFlagType.exterior);
    GameTime var1 = GameTime.getInstance();
         DELTA = var1.getMultiplier();
         if (!WeatherFxMask.playerHasMaskToDraw(IsoCamera.frameState.playerIndex)) {
            if (this.playerIndoors && this.indoorsAlphaMod.value() > 0.0F) {
               this.indoorsAlphaMod.setTarget(this.indoorsAlphaMod.value() - 0.05F * DELTA);
            } else if (!this.playerIndoors && this.indoorsAlphaMod.value() < 1.0F) {
               this.indoorsAlphaMod.setTarget(this.indoorsAlphaMod.value() + 0.05F * DELTA);
            }
         } else {
            this.indoorsAlphaMod.setTarget(1.0F);
         }

         this.indoorsAlphaMod.update(DELTA);
         this.cloudIntensity.update(DELTA);
         this.windIntensity.update(DELTA);
         this.windPrecipIntensity.update(DELTA);
         this.windAngleIntensity.update(DELTA);
         this.precipitationIntensity.update(DELTA);
         this.fogIntensity.update(DELTA);
         if (this.precipitationIsSnow) {
            this.precipitationIntensitySnow.setTarget(this.precipitationIntensity.getTarget());
         } else {
            this.precipitationIntensitySnow.setTarget(0.0F);
         }

         if (!this.precipitationIsSnow) {
            this.precipitationIntensityRain.setTarget(this.precipitationIntensity.getTarget());
         } else {
            this.precipitationIntensityRain.setTarget(0.0F);
         }

         if (this.precipitationIsSnow) {
            this.windAngleMod.setTarget(0.3F);
         } else {
            this.windAngleMod.setTarget(0.6F);
         }

         this.precipitationIntensitySnow.update(DELTA);
         this.precipitationIntensityRain.update(DELTA);
         this.windAngleMod.update(DELTA);
    float var2 = this.fogIntensity.value() * this.indoorsAlphaMod.value();
         this.fogOverlayAlpha = 0.8F * var2;
         if (++this.windUpdCounter > 15.0F) {
            this.windUpdCounter = 0.0F;
            if (this.windAngleIntensity.value() > 0.0F) {
               this.windAngle = lerp(this.windPrecipIntensity.value(), 90.0F, 0.0F + 54.0F * this.windAngleMod.value());
               if (this.windAngleIntensity.value() < 0.5F) {
                  this.windAngleClouds = lerp(this.windAngleIntensity.value() * 2.0F, 90.0F, 0.0F);
               } else {
                  this.windAngleClouds = lerp((this.windAngleIntensity.value() - 0.5F) * 2.0F, 360.0F, 270.0F);
               }
            } else if (this.windAngleIntensity.value() < 0.0F) {
               this.windAngle = lerp(Math.abs(this.windPrecipIntensity.value()), 90.0F, 180.0F - 54.0F * this.windAngleMod.value());
               this.windAngleClouds = lerp(Math.abs(this.windAngleIntensity.value()), 90.0F, 270.0F);
            } else {
               this.windAngle = 90.0F;
            }

            this.windSpeed = this.windSpeedMax * this.windPrecipIntensity.value();
            this.windSpeedFog = this.windSpeedMax * this.windIntensity.value() * (4.0F + 16.0F * Math.abs(this.windAngleIntensity.value()));
            if (this.windSpeed < 1.0F) {
               this.windSpeed = 1.0F;
            }

            if (this.windSpeedFog < 1.0F) {
               this.windSpeedFog = 1.0F;
            }
         }

    float var3 = Core.getInstance().getZoom(IsoPlayer.getInstance().getPlayerNum());
    float var4 = 1.0F - (var3 - 0.5F) * 0.5F * 0.75F;
         ZoomMod = 0.0F;
         if (Core.getInstance().isZoomEnabled() && var3 > 1.0F) {
            ZoomMod = ClimateManager.clamp(0.0F, 1.0F, (var3 - 1.0F) * 0.6666667F);
         }

         if (this.cloudIntensity.value() <= 0.0F) {
            this.cloudParticles.SetParticlesStrength(0.0F);
         } else {
            this.cloudParticles.SetParticlesStrength(1.0F);
         }

         if (this.fogIntensity.value() <= 0.0F) {
            this.fogParticles.SetParticlesStrength(0.0F);
         } else {
            this.fogParticles.SetParticlesStrength(1.0F);
         }

         this.snowParticles.SetParticlesStrength(this.precipitationIntensitySnow.value() * var4);
         this.rainParticles.SetParticlesStrength(this.precipitationIntensityRain.value() * var4);

         for (int var5 = 0; var5 < this.particleRectangles.size(); var5++) {
            if (this.particleRectangles.get(var5).requiresUpdate()) {
               this.particleRectangles.get(var5).update(DELTA);
            }
         }
      }
   }

    void setDebugBounds(bool var1) {
      DEBUG_BOUNDS = var1;
   }

    bool isDebugBounds() {
    return DEBUG_BOUNDS;
   }

    void setWindAngleIntensity(float var1) {
      this.windAngleIntensity.setTarget(var1);
      if (VERBOSE) {
         DebugLog.log("Wind angle intensity = " + this.windAngleIntensity.getTarget());
      }
   }

    float getWindAngleIntensity() {
      return this.windAngleIntensity.value();
   }

    float getRenderWindAngleRain() {
      return this.windAngle;
   }

    void setWindPrecipIntensity(float var1) {
      this.windPrecipIntensity.setTarget(var1);
      if (VERBOSE) {
         DebugLog.log("Wind Precip intensity = " + this.windPrecipIntensity.getTarget());
      }
   }

    float getWindPrecipIntensity() {
      return this.windPrecipIntensity.value();
   }

    void setWindIntensity(float var1) {
      this.windIntensity.setTarget(var1);
      if (VERBOSE) {
         DebugLog.log("Wind intensity = " + this.windIntensity.getTarget());
      }
   }

    float getWindIntensity() {
      return this.windIntensity.value();
   }

    void setFogIntensity(float var1) {
      if (SandboxOptions.instance.MaxFogIntensity.getValue() == 2) {
         var1 = Math.min(var1, 0.75F);
      } else if (SandboxOptions.instance.MaxFogIntensity.getValue() == 3) {
         var1 = Math.min(var1, 0.5F);
      }

      this.fogIntensity.setTarget(var1);
      if (VERBOSE) {
         DebugLog.log("Fog intensity = " + this.fogIntensity.getTarget());
      }
   }

    float getFogIntensity() {
      return this.fogIntensity.value();
   }

    void setCloudIntensity(float var1) {
      this.cloudIntensity.setTarget(var1);
      if (VERBOSE) {
         DebugLog.log("Cloud intensity = " + this.cloudIntensity.getTarget());
      }
   }

    float getCloudIntensity() {
      return this.cloudIntensity.value();
   }

    void setPrecipitationIntensity(float var1) {
      if (SandboxOptions.instance.MaxRainFxIntensity.getValue() == 2) {
         var1 *= 0.75F;
      } else if (SandboxOptions.instance.MaxRainFxIntensity.getValue() == 3) {
         var1 *= 0.5F;
      }

      if (var1 > 0.0F) {
         var1 = 0.05F + 0.95F * var1;
      }

      this.precipitationIntensity.setTarget(var1);
      if (VERBOSE) {
         DebugLog.log("Precipitation intensity = " + this.precipitationIntensity.getTarget());
      }
   }

    float getPrecipitationIntensity() {
      return this.precipitationIntensity.value();
   }

    void setPrecipitationIsSnow(bool var1) {
      this.precipitationIsSnow = var1;
   }

    bool getPrecipitationIsSnow() {
      return this.precipitationIsSnow;
   }

    bool hasCloudsToRender() {
      return this.cloudIntensity.value() > 0.0F || this.particleRectangles.get(ID_CLOUD).requiresUpdate();
   }

    bool hasPrecipitationToRender() {
      return this.precipitationIntensity.value() > 0.0F
         || this.particleRectangles.get(ID_SNOW).requiresUpdate()
         || this.particleRectangles.get(ID_RAIN).requiresUpdate();
   }

    bool hasFogToRender() {
      return this.fogIntensity.value() > 0.0F || this.particleRectangles.get(ID_FOG).requiresUpdate();
   }

    void render() {
      if (!GameServer.bServer) {
         for (int var1 = 0; var1 < this.particleRectangles.size(); var1++) {
            if (var1 == ID_FOG) {
               if (PerformanceSettings.FogQuality != 2) {
                  continue;
               }

               this.renderFogCircle();
            }

            if ((var1 != ID_RAIN && var1 != ID_SNOW || Core.OptionRenderPrecipitation <= 2) && this.particleRectangles.get(var1).requiresUpdate()) {
               this.particleRectangles.get(var1).render();
            }
         }
      }
   }

    void renderLayered(bool var1, bool var2, bool var3) {
      if (var1) {
         this.renderClouds();
      } else if (var2) {
         this.renderFog();
      } else if (var3) {
         this.renderPrecipitation();
      }
   }

    void renderClouds() {
      if (!GameServer.bServer) {
         if (this.particleRectangles.get(ID_CLOUD).requiresUpdate()) {
            this.particleRectangles.get(ID_CLOUD).render();
         }
      }
   }

    void renderFog() {
      if (!GameServer.bServer) {
         this.renderFogCircle();
         if (this.particleRectangles.get(ID_FOG).requiresUpdate()) {
            this.particleRectangles.get(ID_FOG).render();
         }
      }
   }

    void renderPrecipitation() {
      if (!GameServer.bServer) {
         if (this.particleRectangles.get(ID_SNOW).requiresUpdate()) {
            this.particleRectangles.get(ID_SNOW).render();
         }

         if (this.particleRectangles.get(ID_RAIN).requiresUpdate()) {
            this.particleRectangles.get(ID_RAIN).render();
         }
      }
   }

    void renderFogCircle() {
      if (!(this.fogOverlayAlpha <= 0.0F)) {
    int var1 = IsoCamera.frameState.playerIndex;
    float var2 = Core.getInstance().getCurrentPlayerZoom();
    int var3 = IsoCamera.getScreenWidth(var1);
    int var4 = IsoCamera.getScreenHeight(var1);
    int var5 = 2048 - (int)(512.0F * this.fogIntensity.value());
    int var6 = 1024 - (int)(256.0F * this.fogIntensity.value());
         var5 = (int)(var5 / var2);
         var6 = (int)(var6 / var2);
    int var7 = var3 / 2 - var5 / 2;
    int var8 = var4 / 2 - var6 / 2;
         var7 = (int)(var7 - IsoCamera.getRightClickOffX() / var2);
         var8 = (int)(var8 - IsoCamera.getRightClickOffY() / var2);
    int var9 = var7 + var5;
    int var10 = var8 + var6;
         SpriteRenderer.instance.glBind(this.texFogWhite.getID());
         IndieGL.glTexParameteri(3553, 10241, 9728);
         IndieGL.glTexParameteri(3553, 10240, 9728);
         if (s_shader == nullptr) {
            RenderThread.invokeOnRenderContext(() -> s_shader = ShaderManager.instance.getOrCreateShader("fogCircle", false));
         }

         if (s_shader.getShaderProgram().isCompiled()) {
            IndieGL.StartShader(s_shader.getID(), var1);
    int var11 = SpriteRenderer.instance.getMainStateIndex();
            if (s_drawer[var1][var11] == nullptr) {
               s_drawer[var1][var11] = std::make_unique<Drawer>();
            }

            s_drawer[var1][var11].init(var3, var4);
         }

         SpriteRenderer.instance
            .renderi(this.texFogCircle, var7, var8, var5, var6, this.fogColor.r, this.fogColor.g, this.fogColor.b, this.fogOverlayAlpha, nullptr);
         SpriteRenderer.instance.renderi(this.texFogWhite, 0, 0, var7, var4, this.fogColor.r, this.fogColor.g, this.fogColor.b, this.fogOverlayAlpha, nullptr);
         SpriteRenderer.instance.renderi(this.texFogWhite, var7, 0, var5, var8, this.fogColor.r, this.fogColor.g, this.fogColor.b, this.fogOverlayAlpha, nullptr);
         SpriteRenderer.instance
            .renderi(this.texFogWhite, var9, 0, var3 - var9, var4, this.fogColor.r, this.fogColor.g, this.fogColor.b, this.fogOverlayAlpha, nullptr);
         SpriteRenderer.instance
            .renderi(this.texFogWhite, var7, var10, var5, var4 - var10, this.fogColor.r, this.fogColor.g, this.fogColor.b, this.fogOverlayAlpha, nullptr);
         if (s_shader.getShaderProgram().isCompiled()) {
            IndieGL.EndShader();
         }

         if (Core.getInstance().getOffscreenBuffer() != nullptr) {
            if (Core.getInstance().isZoomEnabled() && Core.getInstance().getZoom(var1) > 0.5F) {
               IndieGL.glTexParameteri(3553, 10241, 9729);
            } else {
               IndieGL.glTexParameteri(3553, 10241, 9728);
            }

            if (Core.getInstance().getZoom(var1) == 0.5F) {
               IndieGL.glTexParameteri(3553, 10240, 9728);
            } else {
               IndieGL.glTexParameteri(3553, 10240, 9729);
            }
         }
      }
   }

    static float clamp(float var0, float var1, float var2) {
      var2 = Math.min(var1, var2);
      return Math.max(var0, var2);
   }

    static float lerp(float var0, float var1, float var2) {
      return var1 + var0 * (var2 - var1);
   }

    static float clerp(float var0, float var1, float var2) {
    float var3 = (float)(1.0 - Math.cos(var0 * Math.PI)) / 2.0F;
      return var1 * (1.0F - var3) + var2 * var3;
   }
}
} // namespace fx
} // namespace weather
} // namespace iso
} // namespace zombie
