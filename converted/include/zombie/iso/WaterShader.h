#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Vector4f.h"
#include "org/lwjgl/opengl/ARBShaderObjects.h"
#include "org/lwjgl/opengl/GL11.h"
#include "org/lwjgl/opengl/GL13.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/opengl/Shader.h"
#include "zombie/core/opengl/ShaderProgram.h"
#include "zombie/core/textures/TextureDraw.h"
#include "zombie/iso/sprite/SkyBox.h"

namespace zombie {
namespace iso {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class WaterShader : public Shader {
public:
 int WaterGroundTex;
 int WaterTextureReflectionA;
 int WaterTextureReflectionB;
 int WaterTime;
 int WaterOffset;
 int WaterViewport;
 int WaterReflectionParam;
 int WaterParamWind;
 int WaterParamWindSpeed;
 int WaterParamRainIntensity;

 public WaterShader(const std::string& string) {
 super(string);
 }

 void onCompileSuccess(ShaderProgram shaderProgram) {
 int int0 = shaderProgram.getShaderID();
 this->WaterGroundTex = ARBShaderObjects.glGetUniformLocationARB(int0, "WaterGroundTex");
 this->WaterTextureReflectionA = ARBShaderObjects.glGetUniformLocationARB(int0, "WaterTextureReflectionA");
 this->WaterTextureReflectionB = ARBShaderObjects.glGetUniformLocationARB(int0, "WaterTextureReflectionB");
 this->WaterTime = ARBShaderObjects.glGetUniformLocationARB(int0, "WTime");
 this->WaterOffset = ARBShaderObjects.glGetUniformLocationARB(int0, "WOffset");
 this->WaterViewport = ARBShaderObjects.glGetUniformLocationARB(int0, "WViewport");
 this->WaterReflectionParam = ARBShaderObjects.glGetUniformLocationARB(int0, "WReflectionParam");
 this->WaterParamWind = ARBShaderObjects.glGetUniformLocationARB(int0, "WParamWind");
 this->WaterParamWindSpeed = ARBShaderObjects.glGetUniformLocationARB(int0, "WParamWindSpeed");
 this->WaterParamRainIntensity = ARBShaderObjects.glGetUniformLocationARB(int0, "WParamRainIntensity");
 this->Start();
 if (this->WaterGroundTex != -1) {
 ARBShaderObjects.glUniform1iARB(this->WaterGroundTex, 0);
 }

 if (this->WaterTextureReflectionA != -1) {
 ARBShaderObjects.glUniform1iARB(this->WaterTextureReflectionA, 1);
 }

 if (this->WaterTextureReflectionB != -1) {
 ARBShaderObjects.glUniform1iARB(this->WaterTextureReflectionB, 2);
 }

 this->End();
 }

 void startMainThread(TextureDraw textureDraw, int var2) {
 IsoWater water = IsoWater.getInstance();
 SkyBox skyBox = SkyBox.getInstance();
 textureDraw.u0 = water.getWaterWindX();
 textureDraw.u1 = water.getWaterWindY();
 textureDraw.u2 = water.getWaterWindSpeed();
 textureDraw.u3 = IsoPuddles.getInstance().getRainIntensity();
 textureDraw.v0 = water.getShaderTime();
 textureDraw.v1 = skyBox.getTextureShift();
 }

 void updateWaterParams(TextureDraw textureDraw, int int0) {
 IsoWater water = IsoWater.getInstance();
 SkyBox skyBox = SkyBox.getInstance();
 PlayerCamera playerCamera = SpriteRenderer.instance.getRenderingPlayerCamera(int0);
 GL13.glActiveTexture(33984);
 water.getTextureBottom().bind();
 GL11.glTexEnvi(8960, 8704, 7681);
 GL13.glActiveTexture(33985);
 skyBox.getTextureCurrent().bind();
 GL11.glTexParameteri(3553, 10240, 9729);
 GL11.glTexParameteri(3553, 10241, 9729);
 GL11.glTexEnvi(8960, 8704, 7681);
 GL13.glActiveTexture(33986);
 skyBox.getTexturePrev().bind();
 GL11.glTexParameteri(3553, 10240, 9729);
 GL11.glTexParameteri(3553, 10241, 9729);
 GL11.glTexEnvi(8960, 8704, 7681);
 ARBShaderObjects.glUniform1fARB(this->WaterTime, textureDraw.v0);
 Vector4f vector4f = water.getShaderOffset();
 ARBShaderObjects.glUniform4fARB(this->WaterOffset, vector4f.x - 90000.0F, vector4f.y - 640000.0F, vector4f.z, vector4f.w);
 ARBShaderObjects.glUniform4fARB(
 this->WaterViewport,
 IsoCamera.getOffscreenLeft(int0),
 IsoCamera.getOffscreenTop(int0),
 playerCamera.OffscreenWidth / playerCamera.zoom,
 playerCamera.OffscreenHeight / playerCamera.zoom
 );
 ARBShaderObjects.glUniform1fARB(this->WaterReflectionParam, textureDraw.v1);
 ARBShaderObjects.glUniform2fARB(this->WaterParamWind, textureDraw.u0, textureDraw.u1);
 ARBShaderObjects.glUniform1fARB(this->WaterParamWindSpeed, textureDraw.u2);
 ARBShaderObjects.glUniform1fARB(this->WaterParamRainIntensity, textureDraw.u3);
 }
}
} // namespace iso
} // namespace zombie
