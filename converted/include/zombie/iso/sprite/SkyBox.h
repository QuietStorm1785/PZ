#pragma once
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

namespace zombie {
namespace iso {
namespace sprite {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class SkyBox : public IsoObject {
public:
 static SkyBox instance;
 IsoSpriteInstance def = nullptr;
 TextureFBO textureFBOA;
 TextureFBO textureFBOB;
 bool isCurrentA;
 Shader Effect;
 const UpdateLimit renderLimit = new UpdateLimit(1000L);
 bool isUpdated = false;
 int SkyBoxTime;
 float SkyBoxParamCloudCount;
 float SkyBoxParamCloudSize;
 const Vector3f SkyBoxParamSunLight = new Vector3f();
 const Color SkyBoxParamSunColor = new Color(1.0F, 1.0F, 1.0F);
 const Color SkyBoxParamSkyHColour = new Color(1.0F, 1.0F, 1.0F);
 const Color SkyBoxParamSkyLColour = new Color(1.0F, 1.0F, 1.0F);
 float SkyBoxParamCloudLight;
 float SkyBoxParamStars;
 float SkyBoxParamFog;
 const Vector3f SkyBoxParamWind;
 bool isSetAVG = false;
 float SkyBoxParamCloudCountAVG;
 float SkyBoxParamCloudSizeAVG;
 const Vector3f SkyBoxParamSunLightAVG = new Vector3f();
 const Color SkyBoxParamSunColorAVG = new Color(1.0F, 1.0F, 1.0F);
 const Color SkyBoxParamSkyHColourAVG = new Color(1.0F, 1.0F, 1.0F);
 const Color SkyBoxParamSkyLColourAVG = new Color(1.0F, 1.0F, 1.0F);
 float SkyBoxParamCloudLightAVG;
 float SkyBoxParamStarsAVG;
 float SkyBoxParamFogAVG;
 const Vector3f SkyBoxParamWindINT;
 Texture texAM;
 Texture texPM;
 const Color SkyHColourDay = new Color(0.1F, 0.1F, 0.4F);
 const Color SkyHColourDawn = new Color(0.2F, 0.2F, 0.3F);
 const Color SkyHColourDusk = new Color(0.2F, 0.2F, 0.3F);
 const Color SkyHColourNight = new Color(0.01F, 0.01F, 0.04F);
 const Color SkyLColourDay = new Color(0.1F, 0.45F, 0.7F);
 const Color SkyLColourDawn = new Color(0.1F, 0.4F, 0.6F);
 const Color SkyLColourDusk = new Color(0.1F, 0.4F, 0.6F);
 const Color SkyLColourNight = new Color(0.01F, 0.045F, 0.07F);
 int apiId;

 public static synchronized SkyBox getInstance() {
 if (instance.empty()) {
 instance = std::make_unique<SkyBox>();
 }

 return instance;
 }

 void update(ClimateManager cm) {
 if (!this->isUpdated) {
 this->isUpdated = true;
 GameTime gameTime = GameTime.getInstance();
 ClimateManager.DayInfo dayInfo = cm.getCurrentDay();
 float float0 = dayInfo.season.getDawn();
 float float1 = dayInfo.season.getDusk();
 float float2 = dayInfo.season.getDayHighNoon();
 float float3 = gameTime.getTimeOfDay();
 if (float3 < float0 || float3 > float1) {
 float float4 = 24.0F - float1 + float0;
 if (float3 > float1) {
 float float5 = (float3 - float1) / float4;
 this->SkyHColourDusk.interp(this->SkyHColourDawn, float5, this->SkyBoxParamSkyHColour);
 this->SkyLColourDusk.interp(this->SkyLColourDawn, float5, this->SkyBoxParamSkyLColour);
 this->SkyBoxParamSunLight.set(0.35F, 0.22F, 0.3F);
 this->SkyBoxParamSunLight.normalize();
 this->SkyBoxParamSunLight.mul(Math.min(1.0F, float5 * 5.0F);
 } else {
 float float6 = (24.0F - float1 + float3) / float4;
 this->SkyHColourDusk.interp(this->SkyHColourDawn, float6, this->SkyBoxParamSkyHColour);
 this->SkyLColourDusk.interp(this->SkyLColourDawn, float6, this->SkyBoxParamSkyLColour);
 this->SkyBoxParamSunLight.set(0.35F, 0.22F, 0.3F);
 this->SkyBoxParamSunLight.normalize();
 this->SkyBoxParamSunLight.mul(Math.min(1.0F, (1.0F - float6) * 5.0F);
 }

 this->SkyBoxParamSunColor.set(cm.getGlobalLight().getExterior());
 this->SkyBoxParamSunColor.scale(cm.getNightStrength());
 } else if (float3 < float2) {
 float float7 = (float3 - float0) / (float2 - float0);
 this->SkyHColourDawn.interp(this->SkyHColourDay, float7, this->SkyBoxParamSkyHColour);
 this->SkyLColourDawn.interp(this->SkyLColourDay, float7, this->SkyBoxParamSkyLColour);
 this->SkyBoxParamSunLight.set(4.0F * float7 - 4.0F, 0.22F, 0.3F);
 this->SkyBoxParamSunLight.normalize();
 this->SkyBoxParamSunLight.mul(Math.min(1.0F, float7 * 10.0F);
 this->SkyBoxParamSunColor.set(cm.getGlobalLight().getExterior());
 } else {
 float float8 = (float3 - float2) / (float1 - float2);
 this->SkyHColourDay.interp(this->SkyHColourDusk, float8, this->SkyBoxParamSkyHColour);
 this->SkyLColourDay.interp(this->SkyLColourDusk, float8, this->SkyBoxParamSkyLColour);
 this->SkyBoxParamSunLight.set(4.0F * float8, 0.22F, 0.3F);
 this->SkyBoxParamSunLight.normalize();
 this->SkyBoxParamSunLight.mul(Math.min(1.0F, (1.0F - float8) * 10.0F);
 this->SkyBoxParamSunColor.set(cm.getGlobalLight().getExterior());
 }

 this->SkyBoxParamSkyHColour.interp(this->SkyHColourNight, cm.getNightStrength(), this->SkyBoxParamSkyHColour);
 this->SkyBoxParamSkyLColour.interp(this->SkyLColourNight, cm.getNightStrength(), this->SkyBoxParamSkyLColour);
 this->SkyBoxParamCloudCount = Math.min(Math.max(cm.getCloudIntensity(), cm.getPrecipitationIntensity() * 2.0F), 0.999F);
 this->SkyBoxParamCloudSize = 0.02F + cm.getTemperature() / 70.0F;
 this->SkyBoxParamFog = cm.getFogIntensity();
 this->SkyBoxParamStars = cm.getNightStrength();
 this->SkyBoxParamCloudLight = (float)(1.0 - (1.0 - 1.0 * Math.pow(1000.0, -cm.getPrecipitationIntensity() - cm.getNightStrength())));
 float float9 = (1.0F - (cm.getWindAngleIntensity() + 1.0F) * 0.5F + 0.25F) % 1.0F;
 float9 *= 360.0F;
 this->SkyBoxParamWind.set((float)Math.cos(Math.toRadians(float9), 0.0F, (float)Math.sin(Math.toRadians(float9);
 this->SkyBoxParamWind.mul(cm.getWindIntensity());
 if (!this->isSetAVG) {
 this->isSetAVG = true;
 this->SkyBoxParamCloudCountAVG = this->SkyBoxParamCloudCount;
 this->SkyBoxParamCloudSizeAVG = this->SkyBoxParamCloudSize;
 this->SkyBoxParamSunLightAVG.set(this->SkyBoxParamSunLight);
 this->SkyBoxParamSunColorAVG.set(this->SkyBoxParamSunColor);
 this->SkyBoxParamSkyHColourAVG.set(this->SkyBoxParamSkyHColour);
 this->SkyBoxParamSkyLColourAVG.set(this->SkyBoxParamSkyLColour);
 this->SkyBoxParamCloudLightAVG = this->SkyBoxParamCloudLight;
 this->SkyBoxParamStarsAVG = this->SkyBoxParamStars;
 this->SkyBoxParamFogAVG = this->SkyBoxParamFog;
 this->SkyBoxParamWindINT.set(this->SkyBoxParamWind);
 } else {
 this->SkyBoxParamCloudCountAVG = this->SkyBoxParamCloudCountAVG + (this->SkyBoxParamCloudCount - this->SkyBoxParamCloudCountAVG) * 0.1F;
 this->SkyBoxParamCloudSizeAVG = this->SkyBoxParamCloudSizeAVG + (this->SkyBoxParamCloudSizeAVG + this->SkyBoxParamCloudSize) * 0.1F;
 this->SkyBoxParamSunLightAVG.lerp(this->SkyBoxParamSunLight, 0.1F);
 this->SkyBoxParamSunColorAVG.interp(this->SkyBoxParamSunColor, 0.1F, this->SkyBoxParamSunColorAVG);
 this->SkyBoxParamSkyHColourAVG.interp(this->SkyBoxParamSkyHColour, 0.1F, this->SkyBoxParamSkyHColourAVG);
 this->SkyBoxParamSkyLColourAVG.interp(this->SkyBoxParamSkyLColour, 0.1F, this->SkyBoxParamSkyLColourAVG);
 this->SkyBoxParamCloudLightAVG = this->SkyBoxParamCloudLightAVG + (this->SkyBoxParamCloudLight - this->SkyBoxParamCloudLightAVG) * 0.1F;
 this->SkyBoxParamStarsAVG = this->SkyBoxParamStarsAVG + (this->SkyBoxParamStars - this->SkyBoxParamStarsAVG) * 0.1F;
 this->SkyBoxParamFogAVG = this->SkyBoxParamFogAVG + (this->SkyBoxParamFog - this->SkyBoxParamFogAVG) * 0.1F;
 this->SkyBoxParamWindINT.add(this->SkyBoxParamWind);
 }
 }
 }

 int getShaderTime() {
 return this->SkyBoxTime;
 }

 float getShaderCloudCount() {
 return this->SkyBoxParamCloudCount;
 }

 float getShaderCloudSize() {
 return this->SkyBoxParamCloudSize;
 }

 Vector3f getShaderSunLight() {
 return this->SkyBoxParamSunLight;
 }

 Color getShaderSunColor() {
 return this->SkyBoxParamSunColor;
 }

 Color getShaderSkyHColour() {
 return this->SkyBoxParamSkyHColour;
 }

 Color getShaderSkyLColour() {
 return this->SkyBoxParamSkyLColour;
 }

 float getShaderCloudLight() {
 return this->SkyBoxParamCloudLight;
 }

 float getShaderStars() {
 return this->SkyBoxParamStars;
 }

 float getShaderFog() {
 return this->SkyBoxParamFog;
 }

 Vector3f getShaderWind() {
 return this->SkyBoxParamWindINT;
 }

 public SkyBox() {
 this->texAM = Texture.getSharedTexture("media/textures/CMVehicleReflection/ref_am.png");
 this->texPM = Texture.getSharedTexture("media/textures/CMVehicleReflection/ref_am.png");

 try {
 Texture texture0 = new Texture(512, 512, 16);
 Texture texture1 = new Texture(512, 512, 16);
 this->textureFBOA = new TextureFBO(texture0);
 this->textureFBOB = new TextureFBO(texture1);
 } catch (Exception exception) {
 exception.printStackTrace();
 }

 this->def = IsoSpriteInstance.get(this->sprite);
 this->SkyBoxTime = 0;
 this->SkyBoxParamSunLight.set(0.35F, 0.22F, 0.3F);
 this->SkyBoxParamSunColor.set(1.0F, 0.86F, 0.7F, 1.0F);
 this->SkyBoxParamSkyHColour.set(0.1F, 0.1F, 0.4F, 1.0F);
 this->SkyBoxParamSkyLColour.set(0.1F, 0.45F, 0.7F, 1.0F);
 this->SkyBoxParamCloudLight = 0.99F;
 this->SkyBoxParamCloudCount = 0.3F;
 this->SkyBoxParamCloudSize = 0.2F;
 this->SkyBoxParamFog = 0.0F;
 this->SkyBoxParamStars = 0.0F;
 this->SkyBoxParamWind = new Vector3f(0.0F);
 this->SkyBoxParamWindINT = new Vector3f(0.0F);
 RenderThread.invokeOnRenderContext(() -> {
 if (Core.getInstance().getPerfSkybox() == 0) {
 this->Effect = new SkyBoxShader("skybox_hires");
 } else {
 this->Effect = new SkyBoxShader("skybox");
 }

 if (GL.getCapabilities().OpenGL30) {
 this->apiId = 1;
 }

 if (GL.getCapabilities().GL_ARB_framebuffer_object) {
 this->apiId = 2;
 }

 if (GL.getCapabilities().GL_EXT_framebuffer_object) {
 this->apiId = 3;
 }
 });
 }

 ITexture getTextureCurrent() {
 if (!Core.getInstance().getUseShaders() || Core.getInstance().getPerfSkybox() == 2) {
 return this->texAM;
 } else {
 return this->isCurrentA ? this->textureFBOA.getTexture() : this->textureFBOB.getTexture();
 }
 }

 ITexture getTexturePrev() {
 if (!Core.getInstance().getUseShaders() || Core.getInstance().getPerfSkybox() == 2) {
 return this->texPM;
 } else {
 return this->isCurrentA ? this->textureFBOB.getTexture() : this->textureFBOA.getTexture();
 }
 }

 TextureFBO getTextureFBOPrev() {
 if (!Core.getInstance().getUseShaders() || Core.getInstance().getPerfSkybox() == 2) {
 return nullptr;
 } else {
 return this->isCurrentA ? this->textureFBOB : this->textureFBOA;
 }
 }

 float getTextureShift() {
 return Core.getInstance().getUseShaders() && Core.getInstance().getPerfSkybox() != 2
 ? (float)this->renderLimit.getTimePeriod()
 : 1.0F - GameTime.getInstance().getNight();
 }

 void swapTextureFBO() {
 this->renderLimit.updateTimePeriod();
 this->isCurrentA = !this->isCurrentA;
 }

 void render() {
 if (Core.getInstance().getUseShaders() && Core.getInstance().getPerfSkybox() != 2) {
 if (!this->renderLimit.Check()) {
 if (GameTime.getInstance().getMultiplier() >= 20.0F) {
 this->SkyBoxTime++;
 }
 } else {
 this->SkyBoxTime++;
 int int0 = IsoCamera.frameState.playerIndex;
 int int1 = IsoCamera.getOffscreenLeft(int0);
 int int2 = IsoCamera.getOffscreenTop(int0);
 int int3 = IsoCamera.getOffscreenWidth(int0);
 int int4 = IsoCamera.getOffscreenHeight(int0);
 SpriteRenderer.instance.drawSkyBox(this->Effect, int0, this->apiId, this->getTextureFBOPrev().getBufferId());
 this->isUpdated = false;
 }
 }
 }

 void draw() {
 if (Core.bDebug && DebugOptions.instance.SkyboxShow.getValue()) {
 ((Texture)this->getTextureCurrent()).render(0.0F, 0.0F, 512.0F, 512.0F, 1.0F, 1.0F, 1.0F, 1.0F, nullptr);
 }
 }
}
} // namespace sprite
} // namespace iso
} // namespace zombie
