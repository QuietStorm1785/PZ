#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Matrix4f.h"
#include "zombie/GameTime.h"
#include "zombie/IndieGL.h"
#include "zombie/SandboxOptions.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Color.h"
#include "zombie/core/Core.h"
#include "zombie/core/PerformanceSettings.h"
#include "zombie/core/Rand.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/core/skinnedmodel/shader/Shader.h"
#include "zombie/core/skinnedmodel/shader/ShaderManager.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/core/textures/TextureDraw.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/weather/ClimateManager.h"
#include "zombie/network/GameServer.h"

namespace zombie {
namespace iso {
namespace weather {
namespace fx {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


/**
 * TurboTuTone.
 */
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
 SteppedUpdateFloat windPrecipIntensity = new SteppedUpdateFloat(0.0F, 0.025F, 0.0F, 1.0F);
 SteppedUpdateFloat windIntensity = new SteppedUpdateFloat(0.0F, 0.005F, 0.0F, 1.0F);
 SteppedUpdateFloat windAngleIntensity = new SteppedUpdateFloat(0.0F, 0.005F, -1.0F, 1.0F);
 SteppedUpdateFloat precipitationIntensity = new SteppedUpdateFloat(0.0F, 0.005F, 0.0F, 1.0F);
 SteppedUpdateFloat precipitationIntensitySnow = new SteppedUpdateFloat(0.0F, 0.005F, 0.0F, 1.0F);
 SteppedUpdateFloat precipitationIntensityRain = new SteppedUpdateFloat(0.0F, 0.005F, 0.0F, 1.0F);
 SteppedUpdateFloat cloudIntensity = new SteppedUpdateFloat(0.0F, 0.005F, 0.0F, 1.0F);
 SteppedUpdateFloat fogIntensity = new SteppedUpdateFloat(0.0F, 0.005F, 0.0F, 1.0F);
 SteppedUpdateFloat windAngleMod = new SteppedUpdateFloat(0.0F, 0.005F, 0.0F, 1.0F);
 bool precipitationIsSnow = true;
 float fogOverlayAlpha = 0.0F;
 float windSpeedMax = 6.0F;
 float windSpeed = 0.0F;
 float windSpeedFog = 0.0F;
 float windAngle = 90.0F;
 float windAngleClouds = 90.0F;
 Texture texFogCircle;
 Texture texFogWhite;
 Color fogColor = new Color(1.0F, 1.0F, 1.0F, 1.0F);
 SteppedUpdateFloat indoorsAlphaMod = new SteppedUpdateFloat(1.0F, 0.05F, 0.0F, 1.0F);
 private ArrayList<ParticleRectangle> particleRectangles = new ArrayList<>(0);
 static IsoWeatherFX instance;
 float windUpdCounter = 0.0F;
 static Shader s_shader;
 static IsoWeatherFX.Drawer[][] s_drawer = new IsoWeatherFX.Drawer[4][3];

 public IsoWeatherFX() {
 instance = this;
 }

 void init() {
 if (!GameServer.bServer) {
 int int0 = 0;
 Texture[] textures0 = new Texture[6];

 for (int int1 = 0; int1 < textures0.length; int1++) {
 textures0[int1] = Texture.getSharedTexture("media/textures/weather/clouds_" + int1 + ".png");
 if (textures0[int1] == nullptr) {
 DebugLog.log("Missing texture: media/textures/weather/clouds_" + int1 + ".png");
 }
 }

 this->cloudParticles = new ParticleRectangle(8192, 4096);
 WeatherParticle[] weatherParticles0 = new WeatherParticle[16];

 for (int int2 = 0; int2 < weatherParticles0.length; int2++) {
 Texture texture0 = textures0[Rand.Next(textures0.length)];
 CloudParticle cloudParticle = new CloudParticle(texture0, texture0.getWidth() * 8, texture0.getHeight() * 8);
 cloudParticle.position.set(Rand.Next(0, this->cloudParticles.getWidth()), Rand.Next(0, this->cloudParticles.getHeight()));
 cloudParticle.speed = Rand.Next(0.01F, 0.1F);
 cloudParticle.angleOffset = 180.0F - Rand.Next(0.0F, 360.0F);
 cloudParticle.alpha = Rand.Next(0.25F, 0.75F);
 weatherParticles0[int2] = cloudParticle;
 }

 this->cloudParticles.SetParticles(weatherParticles0);
 this->cloudParticles.SetParticlesStrength(1.0F);
 this->particleRectangles.add(int0, this->cloudParticles);
 ID_CLOUD = int0++;
 if (this->texFogCircle == nullptr) {
 this->texFogCircle = Texture.getSharedTexture("media/textures/weather/fogcircle_tex.png", 35);
 }

 if (this->texFogWhite == nullptr) {
 this->texFogWhite = Texture.getSharedTexture("media/textures/weather/fogwhite_tex.png", 35);
 }

 Texture[] textures1 = new Texture[6];

 for (int int3 = 0; int3 < textures1.length; int3++) {
 textures1[int3] = Texture.getSharedTexture("media/textures/weather/fog_" + int3 + ".png");
 if (textures1[int3] == nullptr) {
 DebugLog.log("Missing texture: media/textures/weather/fog_" + int3 + ".png");
 }
 }

 this->fogParticles = new ParticleRectangle(2048, 1024);
 WeatherParticle[] weatherParticles1 = new WeatherParticle[16];

 for (int int4 = 0; int4 < weatherParticles1.length; int4++) {
 Texture texture1 = textures1[Rand.Next(textures1.length)];
 FogParticle fogParticle = new FogParticle(texture1, texture1.getWidth() * 2, texture1.getHeight() * 2);
 fogParticle.position.set(Rand.Next(0, this->fogParticles.getWidth()), Rand.Next(0, this->fogParticles.getHeight()));
 fogParticle.speed = Rand.Next(0.01F, 0.1F);
 fogParticle.angleOffset = 180.0F - Rand.Next(0.0F, 360.0F);
 fogParticle.alpha = Rand.Next(0.05F, 0.25F);
 weatherParticles1[int4] = fogParticle;
 }

 this->fogParticles.SetParticles(weatherParticles1);
 this->fogParticles.SetParticlesStrength(1.0F);
 this->particleRectangles.add(int0, this->fogParticles);
 ID_FOG = int0++;
 Texture[] textures2 = new Texture[3];

 for (int int5 = 0; int5 < textures2.length; int5++) {
 textures2[int5] = Texture.getSharedTexture("media/textures/weather/snow_" + (int5 + 1) + ".png");
 if (textures2[int5] == nullptr) {
 DebugLog.log("Missing texture: media/textures/weather/snow_" + (int5 + 1) + ".png");
 }
 }

 this->snowParticles = new ParticleRectangle(512, 512);
 WeatherParticle[] weatherParticles2 = new WeatherParticle[1024];

 for (int int6 = 0; int6 < weatherParticles2.length; int6++) {
 SnowParticle snowParticle = new SnowParticle(textures2[Rand.Next(textures2.length)]);
 snowParticle.position.set(Rand.Next(0, this->snowParticles.getWidth()), Rand.Next(0, this->snowParticles.getHeight()));
 snowParticle.speed = Rand.Next(1.0F, 2.0F);
 snowParticle.angleOffset = 15.0F - Rand.Next(0.0F, 30.0F);
 snowParticle.alpha = Rand.Next(0.25F, 0.6F);
 weatherParticles2[int6] = snowParticle;
 }

 this->snowParticles.SetParticles(weatherParticles2);
 this->particleRectangles.add(int0, this->snowParticles);
 ID_SNOW = int0++;
 this->rainParticles = new ParticleRectangle(512, 512);
 WeatherParticle[] weatherParticles3 = new WeatherParticle[1024];

 for (int int7 = 0; int7 < weatherParticles3.length; int7++) {
 RainParticle rainParticle = new RainParticle(this->texFogWhite, Rand.Next(5, 12);
 rainParticle.position.set(Rand.Next(0, this->rainParticles.getWidth()), Rand.Next(0, this->rainParticles.getHeight()));
 rainParticle.speed = Rand.Next(7, 12);
 rainParticle.angleOffset = 3.0F - Rand.Next(0.0F, 6.0F);
 rainParticle.alpha = Rand.Next(0.5F, 0.8F);
 rainParticle.color = new Color(Rand.Next(0.75F, 0.8F), Rand.Next(0.85F, 0.9F), Rand.Next(0.95F, 1.0F), 1.0F);
 weatherParticles3[int7] = rainParticle;
 }

 this->rainParticles.SetParticles(weatherParticles3);
 this->particleRectangles.add(int0, this->rainParticles);
 ID_RAIN = int0++;
 }
 }

 void update() {
 if (!GameServer.bServer) {
 this->playerIndoors = IsoCamera.frameState.CamCharacterSquare != nullptr && !IsoCamera.frameState.CamCharacterSquare.Is(IsoFlagType.exterior);
 GameTime gameTime = GameTime.getInstance();
 DELTA = gameTime.getMultiplier();
 if (!WeatherFxMask.playerHasMaskToDraw(IsoCamera.frameState.playerIndex) {
 if (this->playerIndoors && this->indoorsAlphaMod.value() > 0.0F) {
 this->indoorsAlphaMod.setTarget(this->indoorsAlphaMod.value() - 0.05F * DELTA);
 } else if (!this->playerIndoors && this->indoorsAlphaMod.value() < 1.0F) {
 this->indoorsAlphaMod.setTarget(this->indoorsAlphaMod.value() + 0.05F * DELTA);
 }
 } else {
 this->indoorsAlphaMod.setTarget(1.0F);
 }

 this->indoorsAlphaMod.update(DELTA);
 this->cloudIntensity.update(DELTA);
 this->windIntensity.update(DELTA);
 this->windPrecipIntensity.update(DELTA);
 this->windAngleIntensity.update(DELTA);
 this->precipitationIntensity.update(DELTA);
 this->fogIntensity.update(DELTA);
 if (this->precipitationIsSnow) {
 this->precipitationIntensitySnow.setTarget(this->precipitationIntensity.getTarget());
 } else {
 this->precipitationIntensitySnow.setTarget(0.0F);
 }

 if (!this->precipitationIsSnow) {
 this->precipitationIntensityRain.setTarget(this->precipitationIntensity.getTarget());
 } else {
 this->precipitationIntensityRain.setTarget(0.0F);
 }

 if (this->precipitationIsSnow) {
 this->windAngleMod.setTarget(0.3F);
 } else {
 this->windAngleMod.setTarget(0.6F);
 }

 this->precipitationIntensitySnow.update(DELTA);
 this->precipitationIntensityRain.update(DELTA);
 this->windAngleMod.update(DELTA);
 float float0 = this->fogIntensity.value() * this->indoorsAlphaMod.value();
 this->fogOverlayAlpha = 0.8F * float0;
 if (++this->windUpdCounter > 15.0F) {
 this->windUpdCounter = 0.0F;
 if (this->windAngleIntensity.value() > 0.0F) {
 this->windAngle = lerp(this->windPrecipIntensity.value(), 90.0F, 0.0F + 54.0F * this->windAngleMod.value());
 if (this->windAngleIntensity.value() < 0.5F) {
 this->windAngleClouds = lerp(this->windAngleIntensity.value() * 2.0F, 90.0F, 0.0F);
 } else {
 this->windAngleClouds = lerp((this->windAngleIntensity.value() - 0.5F) * 2.0F, 360.0F, 270.0F);
 }
 } else if (this->windAngleIntensity.value() < 0.0F) {
 this->windAngle = lerp(Math.abs(this->windPrecipIntensity.value()), 90.0F, 180.0F - 54.0F * this->windAngleMod.value());
 this->windAngleClouds = lerp(Math.abs(this->windAngleIntensity.value()), 90.0F, 270.0F);
 } else {
 this->windAngle = 90.0F;
 }

 this->windSpeed = this->windSpeedMax * this->windPrecipIntensity.value();
 this->windSpeedFog = this->windSpeedMax * this->windIntensity.value() * (4.0F + 16.0F * Math.abs(this->windAngleIntensity.value()));
 if (this->windSpeed < 1.0F) {
 this->windSpeed = 1.0F;
 }

 if (this->windSpeedFog < 1.0F) {
 this->windSpeedFog = 1.0F;
 }
 }

 float float1 = Core.getInstance().getZoom(IsoPlayer.getInstance().getPlayerNum());
 float float2 = 1.0F - (float1 - 0.5F) * 0.5F * 0.75F;
 ZoomMod = 0.0F;
 if (Core.getInstance().isZoomEnabled() && float1 > 1.0F) {
 ZoomMod = ClimateManager.clamp(0.0F, 1.0F, (float1 - 1.0F) * 0.6666667F);
 }

 if (this->cloudIntensity.value() <= 0.0F) {
 this->cloudParticles.SetParticlesStrength(0.0F);
 } else {
 this->cloudParticles.SetParticlesStrength(1.0F);
 }

 if (this->fogIntensity.value() <= 0.0F) {
 this->fogParticles.SetParticlesStrength(0.0F);
 } else {
 this->fogParticles.SetParticlesStrength(1.0F);
 }

 this->snowParticles.SetParticlesStrength(this->precipitationIntensitySnow.value() * float2);
 this->rainParticles.SetParticlesStrength(this->precipitationIntensityRain.value() * float2);

 for (int int0 = 0; int0 < this->particleRectangles.size(); int0++) {
 if (this->particleRectangles.get(int0).requiresUpdate()) {
 this->particleRectangles.get(int0).update(DELTA);
 }
 }
 }
 }

 void setDebugBounds(bool b) {
 DEBUG_BOUNDS = b;
 }

 bool isDebugBounds() {
 return DEBUG_BOUNDS;
 }

 void setWindAngleIntensity(float intensity) {
 this->windAngleIntensity.setTarget(intensity);
 if (VERBOSE) {
 DebugLog.log("Wind angle intensity = " + this->windAngleIntensity.getTarget());
 }
 }

 float getWindAngleIntensity() {
 return this->windAngleIntensity.value();
 }

 float getRenderWindAngleRain() {
 return this->windAngle;
 }

 void setWindPrecipIntensity(float intensity) {
 this->windPrecipIntensity.setTarget(intensity);
 if (VERBOSE) {
 DebugLog.log("Wind Precip intensity = " + this->windPrecipIntensity.getTarget());
 }
 }

 float getWindPrecipIntensity() {
 return this->windPrecipIntensity.value();
 }

 void setWindIntensity(float intensity) {
 this->windIntensity.setTarget(intensity);
 if (VERBOSE) {
 DebugLog.log("Wind intensity = " + this->windIntensity.getTarget());
 }
 }

 float getWindIntensity() {
 return this->windIntensity.value();
 }

 void setFogIntensity(float intensity) {
 if (SandboxOptions.instance.MaxFogIntensity.getValue() == 2) {
 intensity = Math.min(intensity, 0.75F);
 } else if (SandboxOptions.instance.MaxFogIntensity.getValue() == 3) {
 intensity = Math.min(intensity, 0.5F);
 }

 this->fogIntensity.setTarget(intensity);
 if (VERBOSE) {
 DebugLog.log("Fog intensity = " + this->fogIntensity.getTarget());
 }
 }

 float getFogIntensity() {
 return this->fogIntensity.value();
 }

 void setCloudIntensity(float intensity) {
 this->cloudIntensity.setTarget(intensity);
 if (VERBOSE) {
 DebugLog.log("Cloud intensity = " + this->cloudIntensity.getTarget());
 }
 }

 float getCloudIntensity() {
 return this->cloudIntensity.value();
 }

 void setPrecipitationIntensity(float intensity) {
 if (SandboxOptions.instance.MaxRainFxIntensity.getValue() == 2) {
 intensity *= 0.75F;
 } else if (SandboxOptions.instance.MaxRainFxIntensity.getValue() == 3) {
 intensity *= 0.5F;
 }

 if (intensity > 0.0F) {
 intensity = 0.05F + 0.95F * intensity;
 }

 this->precipitationIntensity.setTarget(intensity);
 if (VERBOSE) {
 DebugLog.log("Precipitation intensity = " + this->precipitationIntensity.getTarget());
 }
 }

 float getPrecipitationIntensity() {
 return this->precipitationIntensity.value();
 }

 void setPrecipitationIsSnow(bool b) {
 this->precipitationIsSnow = b;
 }

 bool getPrecipitationIsSnow() {
 return this->precipitationIsSnow;
 }

 bool hasCloudsToRender() {
 return this->cloudIntensity.value() > 0.0F || this->particleRectangles.get(ID_CLOUD).requiresUpdate();
 }

 bool hasPrecipitationToRender() {
 return this->precipitationIntensity.value() > 0.0F
 || this->particleRectangles.get(ID_SNOW).requiresUpdate()
 || this->particleRectangles.get(ID_RAIN).requiresUpdate();
 }

 bool hasFogToRender() {
 return this->fogIntensity.value() > 0.0F || this->particleRectangles.get(ID_FOG).requiresUpdate();
 }

 void render() {
 if (!GameServer.bServer) {
 for (int int0 = 0; int0 < this->particleRectangles.size(); int0++) {
 if (int0 == ID_FOG) {
 if (PerformanceSettings.FogQuality != 2) {
 continue;
 }

 this->renderFogCircle();
 }

 if ((int0 != ID_RAIN && int0 != ID_SNOW || Core.OptionRenderPrecipitation <= 2) && this->particleRectangles.get(int0).requiresUpdate()) {
 this->particleRectangles.get(int0).render();
 }
 }
 }
 }

 void renderLayered(bool doClouds, bool doFog, bool doPrecip) {
 if (doClouds) {
 this->renderClouds();
 } else if (doFog) {
 this->renderFog();
 } else if (doPrecip) {
 this->renderPrecipitation();
 }
 }

 void renderClouds() {
 if (!GameServer.bServer) {
 if (this->particleRectangles.get(ID_CLOUD).requiresUpdate()) {
 this->particleRectangles.get(ID_CLOUD).render();
 }
 }
 }

 void renderFog() {
 if (!GameServer.bServer) {
 this->renderFogCircle();
 if (this->particleRectangles.get(ID_FOG).requiresUpdate()) {
 this->particleRectangles.get(ID_FOG).render();
 }
 }
 }

 void renderPrecipitation() {
 if (!GameServer.bServer) {
 if (this->particleRectangles.get(ID_SNOW).requiresUpdate()) {
 this->particleRectangles.get(ID_SNOW).render();
 }

 if (this->particleRectangles.get(ID_RAIN).requiresUpdate()) {
 this->particleRectangles.get(ID_RAIN).render();
 }
 }
 }

 void renderFogCircle() {
 if (!(this->fogOverlayAlpha <= 0.0F) {
 int int0 = IsoCamera.frameState.playerIndex;
 float float0 = Core.getInstance().getCurrentPlayerZoom();
 int int1 = IsoCamera.getScreenWidth(int0);
 int int2 = IsoCamera.getScreenHeight(int0);
 int int3 = 2048 - (int)(512.0F * this->fogIntensity.value());
 int int4 = 1024 - (int)(256.0F * this->fogIntensity.value());
 int3 = (int)(int3 / float0);
 int4 = (int)(int4 / float0);
 int int5 = int1 / 2 - int3 / 2;
 int int6 = int2 / 2 - int4 / 2;
 int5 = (int)(int5 - IsoCamera.getRightClickOffX() / float0);
 int6 = (int)(int6 - IsoCamera.getRightClickOffY() / float0);
 int int7 = int5 + int3;
 int int8 = int6 + int4;
 SpriteRenderer.instance.glBind(this->texFogWhite.getID());
 IndieGL.glTexParameteri(3553, 10241, 9728);
 IndieGL.glTexParameteri(3553, 10240, 9728);
 if (s_shader == nullptr) {
 RenderThread.invokeOnRenderContext(() -> s_shader = ShaderManager.instance.getOrCreateShader("fogCircle", false);
 }

 if (s_shader.getShaderProgram().isCompiled()) {
 IndieGL.StartShader(s_shader.getID(), int0);
 int int9 = SpriteRenderer.instance.getMainStateIndex();
 if (s_drawer[int0][int9] == nullptr) {
 s_drawer[int0][int9] = new IsoWeatherFX.Drawer();
 }

 s_drawer[int0][int9].init(int1, int2);
 }

 SpriteRenderer.instance
 .renderi(this->texFogCircle, int5, int6, int3, int4, this->fogColor.r, this->fogColor.g, this->fogColor.b, this->fogOverlayAlpha, nullptr);
 SpriteRenderer.instance.renderi(this->texFogWhite, 0, 0, int5, int2, this->fogColor.r, this->fogColor.g, this->fogColor.b, this->fogOverlayAlpha, nullptr);
 SpriteRenderer.instance
 .renderi(this->texFogWhite, int5, 0, int3, int6, this->fogColor.r, this->fogColor.g, this->fogColor.b, this->fogOverlayAlpha, nullptr);
 SpriteRenderer.instance
 .renderi(this->texFogWhite, int7, 0, int1 - int7, int2, this->fogColor.r, this->fogColor.g, this->fogColor.b, this->fogOverlayAlpha, nullptr);
 SpriteRenderer.instance
 .renderi(this->texFogWhite, int5, int8, int3, int2 - int8, this->fogColor.r, this->fogColor.g, this->fogColor.b, this->fogOverlayAlpha, nullptr);
 if (s_shader.getShaderProgram().isCompiled()) {
 IndieGL.EndShader();
 }

 if (Core.getInstance().getOffscreenBuffer() != nullptr) {
 if (Core.getInstance().isZoomEnabled() && Core.getInstance().getZoom(int0) > 0.5F) {
 IndieGL.glTexParameteri(3553, 10241, 9729);
 } else {
 IndieGL.glTexParameteri(3553, 10241, 9728);
 }

 if (Core.getInstance().getZoom(int0) == 0.5F) {
 IndieGL.glTexParameteri(3553, 10240, 9728);
 } else {
 IndieGL.glTexParameteri(3553, 10240, 9729);
 }
 }
 }
 }

 static float clamp(float min, float max, float val) {
 val = Math.min(max, val);
 return Math.max(min, val);
 }

 static float lerp(float t, float a, float b) {
 return a + t * (b - a);
 }

 static float clerp(float t, float a, float b) {
 float float0 = (float)(1.0 - Math.cos(t * Math.PI) / 2.0F;
 return a * (1.0F - float0) + b * float0;
 }

 private static class Drawer extends TextureDraw.GenericDrawer {
 static const Matrix4f s_matrix4f = new Matrix4f();
 org.lwjgl.util.vector.Matrix4f m_mvp = new org.lwjgl.util.vector.Matrix4f();
 int m_width;
 int m_height;
 bool m_bSet = false;

 void init(int int1, int int0) {
 if (int1 != this->m_width || int0 != this->m_height || !this->m_bSet) {
 this->m_width = int1;
 this->m_height = int0;
 this->m_bSet = false;
 s_matrix4f.setOrtho(0.0F, this->m_width, this->m_height, 0.0F, -1.0F, 1.0F);
 PZMath.convertMatrix(s_matrix4f, this->m_mvp);
 this->m_mvp.transpose();
 SpriteRenderer.instance.drawGeneric(this);
 }
 }

 void render() {
 IsoWeatherFX.s_shader.getShaderProgram().setValue("u_mvp", this->m_mvp);
 this->m_bSet = true;
 }
 }
}
} // namespace fx
} // namespace weather
} // namespace iso
} // namespace zombie
