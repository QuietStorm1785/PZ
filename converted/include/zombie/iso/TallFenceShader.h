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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class TallFenceShader {
public:
 static const TallFenceShader instance = new TallFenceShader();
 ShaderProgram shaderProgram;
 int u_alpha;
 int u_outlineColor;
 int u_stepSize;

 void initShader() {
 this->shaderProgram = ShaderProgram.createShaderProgram("tallFence", false, true);
 if (this->shaderProgram.isCompiled()) {
 this->u_alpha = ARBShaderObjects.glGetUniformLocationARB(this->shaderProgram.getShaderID(), "u_alpha");
 this->u_stepSize = ARBShaderObjects.glGetUniformLocationARB(this->shaderProgram.getShaderID(), "u_stepSize");
 this->u_outlineColor = ARBShaderObjects.glGetUniformLocationARB(this->shaderProgram.getShaderID(), "u_outlineColor");
 ARBShaderObjects.glUseProgramObjectARB(this->shaderProgram.getShaderID());
 ARBShaderObjects.glUniform2fARB(this->u_stepSize, 0.001F, 0.001F);
 ARBShaderObjects.glUseProgramObjectARB(0);
 }
 }

 void setAlpha(float float0) {
 SpriteRenderer.instance.ShaderUpdate1f(this->shaderProgram.getShaderID(), this->u_alpha, float0);
 }

 void setOutlineColor(float float0, float float1, float float2, float float3) {
 SpriteRenderer.instance.ShaderUpdate4f(this->shaderProgram.getShaderID(), this->u_outlineColor, float0, float1, float2, float3);
 }

 void setStepSize(float float0, int int1, int int0) {
 SpriteRenderer.instance.ShaderUpdate2f(this->shaderProgram.getShaderID(), this->u_stepSize, float0 / int1, float0 / int0);
 }

 bool StartShader() {
 if (this->shaderProgram == nullptr) {
 RenderThread.invokeOnRenderContext(this::initShader);
 }

 if (this->shaderProgram.isCompiled()) {
 IndieGL.StartShader(this->shaderProgram.getShaderID(), 0);
 return true;
 } else {
 return false;
 }
 }
}
} // namespace iso
} // namespace zombie
