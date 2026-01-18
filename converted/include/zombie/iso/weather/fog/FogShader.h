#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/opengl/ARBShaderObjects.h"
#include "zombie/IndieGL.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/core/opengl/ShaderProgram.h"

namespace zombie {
namespace iso {
namespace weather {
namespace fog {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class FogShader {
public:
 static const FogShader instance = new FogShader();
 ShaderProgram shaderProgram;
 int noiseTexture;
 int screenInfo;
 int textureInfo;
 int rectangleInfo;
 int worldOffset;
 int scalingInfo;
 int colorInfo;
 int paramInfo;
 int cameraInfo;

 void initShader() {
 this->shaderProgram = ShaderProgram.createShaderProgram("fog", false, true);
 if (this->shaderProgram.isCompiled()) {
 this->noiseTexture = ARBShaderObjects.glGetUniformLocationARB(this->shaderProgram.getShaderID(), "NoiseTexture");
 this->screenInfo = ARBShaderObjects.glGetUniformLocationARB(this->shaderProgram.getShaderID(), "screenInfo");
 this->textureInfo = ARBShaderObjects.glGetUniformLocationARB(this->shaderProgram.getShaderID(), "textureInfo");
 this->rectangleInfo = ARBShaderObjects.glGetUniformLocationARB(this->shaderProgram.getShaderID(), "rectangleInfo");
 this->scalingInfo = ARBShaderObjects.glGetUniformLocationARB(this->shaderProgram.getShaderID(), "scalingInfo");
 this->colorInfo = ARBShaderObjects.glGetUniformLocationARB(this->shaderProgram.getShaderID(), "colorInfo");
 this->worldOffset = ARBShaderObjects.glGetUniformLocationARB(this->shaderProgram.getShaderID(), "worldOffset");
 this->paramInfo = ARBShaderObjects.glGetUniformLocationARB(this->shaderProgram.getShaderID(), "paramInfo");
 this->cameraInfo = ARBShaderObjects.glGetUniformLocationARB(this->shaderProgram.getShaderID(), "cameraInfo");
 ARBShaderObjects.glUseProgramObjectARB(this->shaderProgram.getShaderID());
 ARBShaderObjects.glUseProgramObjectARB(0);
 }
 }

 void setScreenInfo(float float0, float float1, float float2, float float3) {
 SpriteRenderer.instance.ShaderUpdate4f(this->shaderProgram.getShaderID(), this->screenInfo, float0, float1, float2, float3);
 }

 void setTextureInfo(float float0, float float1, float float2, float float3) {
 SpriteRenderer.instance.ShaderUpdate4f(this->shaderProgram.getShaderID(), this->textureInfo, float0, float1, float2, float3);
 }

 void setRectangleInfo(float float0, float float1, float float2, float float3) {
 SpriteRenderer.instance.ShaderUpdate4f(this->shaderProgram.getShaderID(), this->rectangleInfo, float0, float1, float2, float3);
 }

 void setScalingInfo(float float0, float float1, float float2, float float3) {
 SpriteRenderer.instance.ShaderUpdate4f(this->shaderProgram.getShaderID(), this->scalingInfo, float0, float1, float2, float3);
 }

 void setColorInfo(float float0, float float1, float float2, float float3) {
 SpriteRenderer.instance.ShaderUpdate4f(this->shaderProgram.getShaderID(), this->colorInfo, float0, float1, float2, float3);
 }

 void setWorldOffset(float float0, float float1, float float2, float float3) {
 SpriteRenderer.instance.ShaderUpdate4f(this->shaderProgram.getShaderID(), this->worldOffset, float0, float1, float2, float3);
 }

 void setParamInfo(float float0, float float1, float float2, float float3) {
 SpriteRenderer.instance.ShaderUpdate4f(this->shaderProgram.getShaderID(), this->paramInfo, float0, float1, float2, float3);
 }

 void setCameraInfo(float float0, float float1, float float2, float float3) {
 SpriteRenderer.instance.ShaderUpdate4f(this->shaderProgram.getShaderID(), this->cameraInfo, float0, float1, float2, float3);
 }

 bool StartShader() {
 if (this->shaderProgram.empty()) {
 RenderThread.invokeOnRenderContext(this::initShader);
 }

 if (this->shaderProgram.isCompiled()) {
 IndieGL.StartShader(this->shaderProgram.getShaderID(), 0);
 return true;
 } else {
 return false;
 }
 }

 void reloadShader() {
 if (this->shaderProgram != nullptr) {
 this->shaderProgram = nullptr;
 }
 }
}
} // namespace fog
} // namespace weather
} // namespace iso
} // namespace zombie
