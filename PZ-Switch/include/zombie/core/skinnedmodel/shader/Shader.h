#pragma once
#include "org/joml/Math.h"
#include "org/joml/Vector4f.h"
#include "org/lwjgl/opengl/ARBShaderObjects.h"
#include "org/lwjgl/opengl/GL20.h"
#include "org/lwjgl/util/vector/Matrix4f.h"
#include "org/lwjgl/util/vector/Vector3f.h"
#include "org/lwjglx/BufferUtils.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/opengl/PZGLUtil.h"
#include "zombie/core/opengl/ShaderProgram.h"
#include "zombie/core/skinnedmodel/model/ModelInstance.h"
#include "zombie/core/skinnedmodel/model/ModelInstanceRenderData.h"
#include "zombie/core/skinnedmodel/model/ModelSlotRenderData.h"
#include "zombie/core/textures/SmartTexture.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerGUI.h"
#include "zombie/vehicles/BaseVehicle.h"
#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace shader {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Shader {
public:
 int HueChange;
 int LightingAmount;
 int MirrorXID;
 int TransformMatrixID = 0;
 const std::string name;
 const ShaderProgram m_shaderProgram;
 int MatrixID = 0;
 int Light0Direction;
 int Light0Colour;
 int Light1Direction;
 int Light1Colour;
 int Light2Direction;
 int Light2Colour;
 int Light3Direction;
 int Light3Colour;
 int Light4Direction;
 int Light4Colour;
 int TintColour;
 int Texture0;
 int TexturePainColor;
 int TextureRust;
 int TextureRustA;
 int TextureMask;
 int TextureLights;
 int TextureDamage1Overlay;
 int TextureDamage1Shell;
 int TextureDamage2Overlay;
 int TextureDamage2Shell;
 int TextureUninstall1;
 int TextureUninstall2;
 int TextureLightsEnables1;
 int TextureLightsEnables2;
 int TextureDamage1Enables1;
 int TextureDamage1Enables2;
 int TextureDamage2Enables1;
 int TextureDamage2Enables2;
 int MatBlood1Enables1;
 int MatBlood1Enables2;
 int MatBlood2Enables1;
 int MatBlood2Enables2;
 int Alpha;
 int TextureReflectionA;
 int TextureReflectionB;
 int ReflectionParam;
 int BoneIndicesAttrib;
 int BoneWeightsAttrib;
 int UVScale;
 const bool bStatic;
 static FloatBuffer floatBuffer;
 static const int MAX_BONES = 64;
 static const Vector3f tempVec3f = new Vector3f();
 const FloatBuffer floatBuffer2 = BufferUtils.createFloatBuffer(16);

public
 Shader(const std::string &_name, bool _bStatic) {
 this->name = _name;
 this->m_shaderProgram =
 ShaderProgram.createShaderProgram(_name, _bStatic, false);
 this->m_shaderProgram.addCompileListener(this ::onProgramCompiled);
 this->bStatic = _bStatic;
 this->compile();
 }

 bool isStatic() { return this->bStatic; }

 ShaderProgram getShaderProgram() { return this->m_shaderProgram; }

 void onProgramCompiled(ShaderProgram var1) {
 this->Start();
 int int0 = this->m_shaderProgram.getShaderID();
 if (!this->bStatic) {
 this->MatrixID =
 ARBShaderObjects.glGetUniformLocationARB(int0, "MatrixPalette");
 } else {
 this->TransformMatrixID =
 ARBShaderObjects.glGetUniformLocationARB(int0, "transform");
 }

 this->HueChange =
 ARBShaderObjects.glGetUniformLocationARB(int0, "HueChange");
 this->LightingAmount =
 ARBShaderObjects.glGetUniformLocationARB(int0, "LightingAmount");
 this->Light0Colour =
 ARBShaderObjects.glGetUniformLocationARB(int0, "Light0Colour");
 this->Light0Direction =
 ARBShaderObjects.glGetUniformLocationARB(int0, "Light0Direction");
 this->Light1Colour =
 ARBShaderObjects.glGetUniformLocationARB(int0, "Light1Colour");
 this->Light1Direction =
 ARBShaderObjects.glGetUniformLocationARB(int0, "Light1Direction");
 this->Light2Colour =
 ARBShaderObjects.glGetUniformLocationARB(int0, "Light2Colour");
 this->Light2Direction =
 ARBShaderObjects.glGetUniformLocationARB(int0, "Light2Direction");
 this->Light3Colour =
 ARBShaderObjects.glGetUniformLocationARB(int0, "Light3Colour");
 this->Light3Direction =
 ARBShaderObjects.glGetUniformLocationARB(int0, "Light3Direction");
 this->Light4Colour =
 ARBShaderObjects.glGetUniformLocationARB(int0, "Light4Colour");
 this->Light4Direction =
 ARBShaderObjects.glGetUniformLocationARB(int0, "Light4Direction");
 this->TintColour =
 ARBShaderObjects.glGetUniformLocationARB(int0, "TintColour");
 this->Texture0 = ARBShaderObjects.glGetUniformLocationARB(int0, "Texture0");
 this->TexturePainColor =
 ARBShaderObjects.glGetUniformLocationARB(int0, "TexturePainColor");
 this->TextureRust =
 ARBShaderObjects.glGetUniformLocationARB(int0, "TextureRust");
 this->TextureMask =
 ARBShaderObjects.glGetUniformLocationARB(int0, "TextureMask");
 this->TextureLights =
 ARBShaderObjects.glGetUniformLocationARB(int0, "TextureLights");
 this->TextureDamage1Overlay =
 ARBShaderObjects.glGetUniformLocationARB(int0, "TextureDamage1Overlay");
 this->TextureDamage1Shell =
 ARBShaderObjects.glGetUniformLocationARB(int0, "TextureDamage1Shell");
 this->TextureDamage2Overlay =
 ARBShaderObjects.glGetUniformLocationARB(int0, "TextureDamage2Overlay");
 this->TextureDamage2Shell =
 ARBShaderObjects.glGetUniformLocationARB(int0, "TextureDamage2Shell");
 this->TextureRustA =
 ARBShaderObjects.glGetUniformLocationARB(int0, "TextureRustA");
 this->TextureUninstall1 =
 ARBShaderObjects.glGetUniformLocationARB(int0, "TextureUninstall1");
 this->TextureUninstall2 =
 ARBShaderObjects.glGetUniformLocationARB(int0, "TextureUninstall2");
 this->TextureLightsEnables1 =
 ARBShaderObjects.glGetUniformLocationARB(int0, "TextureLightsEnables1");
 this->TextureLightsEnables2 =
 ARBShaderObjects.glGetUniformLocationARB(int0, "TextureLightsEnables2");
 this->TextureDamage1Enables1 = ARBShaderObjects.glGetUniformLocationARB(
 int0, "TextureDamage1Enables1");
 this->TextureDamage1Enables2 = ARBShaderObjects.glGetUniformLocationARB(
 int0, "TextureDamage1Enables2");
 this->TextureDamage2Enables1 = ARBShaderObjects.glGetUniformLocationARB(
 int0, "TextureDamage2Enables1");
 this->TextureDamage2Enables2 = ARBShaderObjects.glGetUniformLocationARB(
 int0, "TextureDamage2Enables2");
 this->MatBlood1Enables1 =
 ARBShaderObjects.glGetUniformLocationARB(int0, "MatBlood1Enables1");
 this->MatBlood1Enables2 =
 ARBShaderObjects.glGetUniformLocationARB(int0, "MatBlood1Enables2");
 this->MatBlood2Enables1 =
 ARBShaderObjects.glGetUniformLocationARB(int0, "MatBlood2Enables1");
 this->MatBlood2Enables2 =
 ARBShaderObjects.glGetUniformLocationARB(int0, "MatBlood2Enables2");
 this->Alpha = ARBShaderObjects.glGetUniformLocationARB(int0, "Alpha");
 this->TextureReflectionA =
 ARBShaderObjects.glGetUniformLocationARB(int0, "TextureReflectionA");
 this->TextureReflectionB =
 ARBShaderObjects.glGetUniformLocationARB(int0, "TextureReflectionB");
 this->ReflectionParam =
 ARBShaderObjects.glGetUniformLocationARB(int0, "ReflectionParam");
 this->UVScale = ARBShaderObjects.glGetUniformLocationARB(int0, "UVScale");
 this->m_shaderProgram.setSamplerUnit("Texture", 0);
 if (this->Texture0 != -1) {
 ARBShaderObjects.glUniform1iARB(this->Texture0, 0);
 }

 if (this->TextureRust != -1) {
 ARBShaderObjects.glUniform1iARB(this->TextureRust, 1);
 }

 if (this->TextureMask != -1) {
 ARBShaderObjects.glUniform1iARB(this->TextureMask, 2);
 }

 if (this->TextureLights != -1) {
 ARBShaderObjects.glUniform1iARB(this->TextureLights, 3);
 }

 if (this->TextureDamage1Overlay != -1) {
 ARBShaderObjects.glUniform1iARB(this->TextureDamage1Overlay, 4);
 }

 if (this->TextureDamage1Shell != -1) {
 ARBShaderObjects.glUniform1iARB(this->TextureDamage1Shell, 5);
 }

 if (this->TextureDamage2Overlay != -1) {
 ARBShaderObjects.glUniform1iARB(this->TextureDamage2Overlay, 6);
 }

 if (this->TextureDamage2Shell != -1) {
 ARBShaderObjects.glUniform1iARB(this->TextureDamage2Shell, 7);
 }

 if (this->TextureReflectionA != -1) {
 ARBShaderObjects.glUniform1iARB(this->TextureReflectionA, 8);
 }

 if (this->TextureReflectionB != -1) {
 ARBShaderObjects.glUniform1iARB(this->TextureReflectionB, 9);
 }

 this->MirrorXID = ARBShaderObjects.glGetUniformLocationARB(int0, "MirrorX");
 this->BoneIndicesAttrib = GL20.glGetAttribLocation(int0, "boneIndices");
 this->BoneWeightsAttrib = GL20.glGetAttribLocation(int0, "boneWeights");
 this->End();
 }

 void compile() { this->m_shaderProgram.compile(); }

 void setTexture(Texture tex, const std::string &unitName, int textureUnit) {
 this->m_shaderProgram.setValue(unitName, tex, textureUnit);
 }

 void setUVScale(float float0, float float1) {
 if (this->UVScale > 0) {
 this->m_shaderProgram.setVector2(this->UVScale, float0, float1);
 }
 }

 int getID() { return this->m_shaderProgram.getShaderID(); }

 void Start() { this->m_shaderProgram.Start(); }

 void End() { this->m_shaderProgram.End(); }

 void startCharacter(ModelSlotRenderData slotData,
 ModelInstanceRenderData instData) {
 if (this->bStatic) {
 this->setTransformMatrix(instData.xfrm, true);
 } else {
 this->setMatrixPalette(instData.matrixPalette);
 }

 float float0 = slotData.ambientR * 0.45F;
 float float1 = slotData.ambientG * 0.45F;
 float float2 = slotData.ambientB * 0.45F;
 this->setLights(slotData, 5);
 Texture texture0 = instData.tex != nullptr ? instData.tex : instData.model.tex;
 if (DebugOptions.instance.IsoSprite.CharacterMipmapColors.getValue()) {
 Texture texture1 = texture0 instanceof
 SmartTexture ? ((SmartTexture)texture0).result : texture0;
 if (texture1 != nullptr && texture1.getTextureId() != nullptr &&
 texture1.getTextureId().hasMipMaps()) {
 texture0 = Texture.getEngineMipmapTexture();
 }
 }

 this->setTexture(texture0, "Texture", 0);
 this->setDepthBias(instData.depthBias / 50.0F);
 this->setAmbient(float0, float1, float2);
 this->setLightingAmount(1.0F);
 this->setHueShift(instData.hue);
 this->setTint(instData.tintR, instData.tintG, instData.tintB);
 this->setAlpha(slotData.alpha);
 }

 void setLights(ModelSlotRenderData modelSlotRenderData, int int1) {
 for (int int0 = 0; int0 < int1; int0++) {
 ModelInstance.EffectLight effectLight =
 modelSlotRenderData.effectLights[int0];
 if (GameServer.bServer && ServerGUI.isCreated()) {
 effectLight.r = effectLight.g = effectLight.b = 1.0F;
 }

 this->setLight(int0, effectLight.x, effectLight.y, effectLight.z,
 effectLight.r, effectLight.g, effectLight.b,
 effectLight.radius, modelSlotRenderData.animPlayerAngle,
 modelSlotRenderData.x, modelSlotRenderData.y,
 modelSlotRenderData.z, modelSlotRenderData.object);
 }
 }

 void updateAlpha(IsoGameCharacter chr, int playerIndex) {
 if (chr != nullptr) {
 this->setAlpha(chr.getAlpha(playerIndex);
 }
 }

 void setAlpha(float alpha) {
 ARBShaderObjects.glUniform1fARB(this->Alpha, alpha);
 }

 void updateParams() {}

 void setMatrixPalette(Matrix4f[] matrix4fs) {
 if (!this->bStatic) {
 if (floatBuffer.empty()) {
 floatBuffer = BufferUtils.createFloatBuffer(1024);
 }

 floatBuffer.clear();

 for (auto &matrix4f : matrix4fs)
 matrix4f.store(floatBuffer);
 }

 floatBuffer.flip();
 ARBShaderObjects.glUniformMatrix4fvARB(this->MatrixID, true, floatBuffer);
 }
}

 void setMatrixPalette(FloatBuffer matrixPalette) {
 this->setMatrixPalette(matrixPalette, true);
}

void setMatrixPalette(FloatBuffer matrixPalette, bool transpose) {
 if (!this->bStatic) {
 ARBShaderObjects.glUniformMatrix4fvARB(this->MatrixID, transpose,
 matrixPalette);
 }
}

void setMatrixPalette(org.joml.Matrix4f[] matrix4fs) {
 if (!this->bStatic) {
 if (floatBuffer.empty()) {
 floatBuffer = BufferUtils.createFloatBuffer(1024);
 }

 floatBuffer.clear();

 for (org.joml.Matrix4f matrix4f : matrix4fs) {
 matrix4f.get(floatBuffer);
 floatBuffer.position(floatBuffer.position() + 16);
 }

 floatBuffer.flip();
 ARBShaderObjects.glUniformMatrix4fvARB(this->MatrixID, true, floatBuffer);
 }
}

void setTint(float x, float y, float z) {
 ARBShaderObjects.glUniform3fARB(this->TintColour, x, y, z);
}

void setTextureRustA(float a) {
 ARBShaderObjects.glUniform1fARB(this->TextureRustA, a);
}

void setTexturePainColor(float x, float y, float z, float a) {
 ARBShaderObjects.glUniform4fARB(this->TexturePainColor, x, y, z, a);
}

void setTexturePainColor(org.joml.Vector3f vec, float a) {
 ARBShaderObjects.glUniform4fARB(this->TexturePainColor, vec.x(), vec.y(),
 vec.z(), a);
}

void setTexturePainColor(Vector4f vec) {
 ARBShaderObjects.glUniform4fARB(this->TexturePainColor, vec.x(), vec.y(),
 vec.z(), vec.w());
}

void setReflectionParam(float timesOfDay, float refWindows, float refBody) {
 ARBShaderObjects.glUniform3fARB(this->ReflectionParam, timesOfDay, refWindows,
 refBody);
}

void setTextureUninstall1(float[] floats) {
 this->setMatrix(this->TextureUninstall1, floats);
}

void setTextureUninstall2(float[] floats) {
 this->setMatrix(this->TextureUninstall2, floats);
}

void setTextureLightsEnables1(float[] floats) {
 this->setMatrix(this->TextureLightsEnables1, floats);
}

void setTextureLightsEnables2(float[] floats) {
 this->setMatrix(this->TextureLightsEnables2, floats);
}

void setTextureDamage1Enables1(float[] floats) {
 this->setMatrix(this->TextureDamage1Enables1, floats);
}

void setTextureDamage1Enables2(float[] floats) {
 this->setMatrix(this->TextureDamage1Enables2, floats);
}

void setTextureDamage2Enables1(float[] floats) {
 this->setMatrix(this->TextureDamage2Enables1, floats);
}

void setTextureDamage2Enables2(float[] floats) {
 this->setMatrix(this->TextureDamage2Enables2, floats);
}

void setMatrixBlood1(float[] floats0, float[] floats1) {
 if (this->MatBlood1Enables1 != -1 && this->MatBlood1Enables2 != -1) {
 this->setMatrix(this->MatBlood1Enables1, floats0);
 this->setMatrix(this->MatBlood1Enables2, floats1);
 }
}

void setMatrixBlood2(float[] floats0, float[] floats1) {
 if (this->MatBlood2Enables1 != -1 && this->MatBlood2Enables2 != -1) {
 this->setMatrix(this->MatBlood2Enables1, floats0);
 this->setMatrix(this->MatBlood2Enables2, floats1);
 }
}

void setShaderAlpha(float a) { ARBShaderObjects.glUniform1fARB(this->Alpha, a); }

void setLight(int index, float x, float y, float z, float r, float g, float b,
 float rad, float animPlayerAngle, ModelInstance inst) {
 float float0 = 0.0F;
 float float1 = 0.0F;
 float float2 = 0.0F;
 IsoMovingObject movingObject = inst.object;
 if (movingObject != nullptr) {
 float0 = movingObject.x;
 float1 = movingObject.y;
 float2 = movingObject.z;
 }

 this->setLight(index, x, y, z, r, g, b, rad, animPlayerAngle, float0, float1,
 float2, movingObject);
}

public
void setLight(int index, float x, float y, float z, float r, float g, float b,
 float rad, float animPlayerAngle, float offsetX, float offsetY,
 float offsetZ, IsoMovingObject instObject) {
 PZGLUtil.checkGLError(true);
 int int0 = this->Light0Direction;
 int int1 = this->Light0Colour;
 if (index == 1) {
 int0 = this->Light1Direction;
 int1 = this->Light1Colour;
 }

 if (index == 2) {
 int0 = this->Light2Direction;
 int1 = this->Light2Colour;
 }

 if (index == 3) {
 int0 = this->Light3Direction;
 int1 = this->Light3Colour;
 }

 if (index == 4) {
 int0 = this->Light4Direction;
 int1 = this->Light4Colour;
 }

 if (r + g + b != 0.0F && !(rad <= 0.0F) {
 Vector3f vector3f = tempVec3f;
 if (!Float.isNaN(animPlayerAngle) {
 vector3f.set(x, y, z);
 vector3f.x -= offsetX;
 vector3f.y -= offsetY;
 vector3f.z -= offsetZ;
 } else {
 vector3f.set(x, y, z);
 }

 float float0 = vector3f.length();
 if (float0 < 1.0E-4F) {
 vector3f.set(0.0F, 0.0F, 1.0F);
 } else {
 vector3f.normalise();
 }

 if (!Float.isNaN(animPlayerAngle) {
 float float1 = -animPlayerAngle;
 float float2 = vector3f.x;
 float float3 = vector3f.y;
 vector3f.x = float2 * Math.cos(float1) - float3 * Math.sin(float1);
 vector3f.y = float2 * Math.sin(float1) + float3 * Math.cos(float1);
 }

 float float4 = vector3f.y;
 vector3f.y = vector3f.z;
 vector3f.z = float4;
 if (vector3f.length() < 1.0E-4F) {
 vector3f.set(0.0F, 1.0F, 0.0F);
 }

 vector3f.normalise();
 float float5 = 1.0F - float0 / rad;
 if (float5 < 0.0F) {
 float5 = 0.0F;
 }

 if (float5 > 1.0F) {
 float5 = 1.0F;
 }

 r *= float5;
 g *= float5;
 b *= float5;
 r = PZMath.clamp(r, 0.0F, 1.0F);
 g = PZMath.clamp(g, 0.0F, 1.0F);
 b = PZMath.clamp(b, 0.0F, 1.0F);
 if (instObject instanceof BaseVehicle) {
 this->doVector3(int0, -vector3f.x, vector3f.y, vector3f.z);
 } else {
 this->doVector3(int0, -vector3f.x, vector3f.y, vector3f.z);
 }

 if (instObject instanceof IsoPlayer) {
 bool boolean0 = false;
 }

 this->doVector3(int1, r, g, b);
 PZGLUtil.checkGLErrorThrow("Shader.setLightInternal.");
 } else {
 this->doVector3(int0, 0.0F, 1.0F, 0.0F);
 this->doVector3(int1, 0.0F, 0.0F, 0.0F);
 }
}

void doVector3(int int0, float float0, float float1, float float2) {
 this->m_shaderProgram.setVector3(int0, float0, float1, float2);
}

void setHueShift(float hue) {
 if (this->HueChange > 0) {
 this->m_shaderProgram.setValue("HueChange", hue);
 }
}

void setLightingAmount(float lighting) {
 if (this->LightingAmount > 0) {
 this->m_shaderProgram.setValue("LightingAmount", lighting);
 }
}

void setDepthBias(float bias) {
 this->m_shaderProgram.setValue("DepthBias", bias / 300.0F);
}

void setAmbient(float amb) {
 this->m_shaderProgram.setVector3("AmbientColour", amb, amb, amb);
}

void setAmbient(float ambr, float ambg, float ambb) {
 this->m_shaderProgram.setVector3("AmbientColour", ambr, ambg, ambb);
}

void setTransformMatrix(Matrix4f matrix4f, bool transpose) {
 if (floatBuffer.empty()) {
 floatBuffer = BufferUtils.createFloatBuffer(1024);
 }

 floatBuffer.clear();
 matrix4f.store(floatBuffer);
 floatBuffer.flip();
 ARBShaderObjects.glUniformMatrix4fvARB(this->TransformMatrixID, transpose,
 floatBuffer);
}

void setTransformMatrix(org.joml.Matrix4f matrix4f, bool transpose) {
 this->floatBuffer2.clear();
 matrix4f.get(this->floatBuffer2);
 this->floatBuffer2.position(16);
 this->floatBuffer2.flip();
 ARBShaderObjects.glUniformMatrix4fvARB(this->TransformMatrixID, transpose,
 this->floatBuffer2);
}

void setMatrix(int location, org.joml.Matrix4f matrix4f) {
 this->floatBuffer2.clear();
 matrix4f.get(this->floatBuffer2);
 this->floatBuffer2.position(16);
 this->floatBuffer2.flip();
 ARBShaderObjects.glUniformMatrix4fvARB(location, true, this->floatBuffer2);
}

void setMatrix(int int0, float[] floats) {
 this->floatBuffer2.clear();
 this->floatBuffer2.put(floats);
 this->floatBuffer2.flip();
 ARBShaderObjects.glUniformMatrix4fvARB(int0, true, this->floatBuffer2);
}

bool isVehicleShader() { return this->TextureRust != -1; }
}
} // namespace shader
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
