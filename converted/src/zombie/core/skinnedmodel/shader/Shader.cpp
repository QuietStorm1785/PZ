#include "zombie/core/skinnedmodel/shader/Shader.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace shader {

public
Shader::Shader(const std::string &_name, bool _bStatic) {
  // TODO: Implement Shader
  return nullptr;
}

bool Shader::isStatic() {
  // TODO: Implement isStatic
  return false;
}

ShaderProgram Shader::getShaderProgram() {
  // TODO: Implement getShaderProgram
  return nullptr;
}

void Shader::onProgramCompiled(ShaderProgram var1) {
  // TODO: Implement onProgramCompiled
}

void Shader::compile() {
  // TODO: Implement compile
}

void Shader::setTexture(Texture tex, const std::string &unitName,
                        int textureUnit) {
  // TODO: Implement setTexture
}

void Shader::setUVScale(float float0, float float1) {
  // TODO: Implement setUVScale
}

int Shader::getID() {
  // TODO: Implement getID
  return 0;
}

void Shader::Start() {
  // TODO: Implement Start
}

void Shader::End() {
  // TODO: Implement End
}

void Shader::startCharacter(ModelSlotRenderData slotData,
                            ModelInstanceRenderData instData) {
  // TODO: Implement startCharacter
}

void Shader::setLights(ModelSlotRenderData modelSlotRenderData, int int1) {
  // TODO: Implement setLights
}

void Shader::updateAlpha(IsoGameCharacter chr, int playerIndex) {
  // TODO: Implement updateAlpha
}

void Shader::setAlpha(float alpha) {
  // TODO: Implement setAlpha
}

void Shader::updateParams() {
  // TODO: Implement updateParams
}

void Shader::setMatrixPalette(Matrix4f[] matrix4fs) {
  // TODO: Implement setMatrixPalette
}

void Shader::setMatrixPalette(FloatBuffer matrixPalette) {
  // TODO: Implement setMatrixPalette
}

void Shader::setMatrixPalette(FloatBuffer matrixPalette, bool transpose) {
  // TODO: Implement setMatrixPalette
}

void Shader::setMatrixPalette(org.joml.Matrix4f[] matrix4fs) {
  // TODO: Implement setMatrixPalette
}

void Shader::setTint(float x, float y, float z) {
  // TODO: Implement setTint
}

void Shader::setTextureRustA(float a) {
  // TODO: Implement setTextureRustA
}

void Shader::setTexturePainColor(float x, float y, float z, float a) {
  // TODO: Implement setTexturePainColor
}

void Shader::setTexturePainColor(org.joml.Vector3f vec, float a) {
  // TODO: Implement setTexturePainColor
}

void Shader::setTexturePainColor(Vector4f vec) {
  // TODO: Implement setTexturePainColor
}

void Shader::setReflectionParam(float timesOfDay, float refWindows,
                                float refBody) {
  // TODO: Implement setReflectionParam
}

void Shader::setTextureUninstall1(float[] floats) {
  // TODO: Implement setTextureUninstall1
}

void Shader::setTextureUninstall2(float[] floats) {
  // TODO: Implement setTextureUninstall2
}

void Shader::setTextureLightsEnables1(float[] floats) {
  // TODO: Implement setTextureLightsEnables1
}

void Shader::setTextureLightsEnables2(float[] floats) {
  // TODO: Implement setTextureLightsEnables2
}

void Shader::setTextureDamage1Enables1(float[] floats) {
  // TODO: Implement setTextureDamage1Enables1
}

void Shader::setTextureDamage1Enables2(float[] floats) {
  // TODO: Implement setTextureDamage1Enables2
}

void Shader::setTextureDamage2Enables1(float[] floats) {
  // TODO: Implement setTextureDamage2Enables1
}

void Shader::setTextureDamage2Enables2(float[] floats) {
  // TODO: Implement setTextureDamage2Enables2
}

void Shader::setMatrixBlood1(float[] floats0, float[] floats1) {
  // TODO: Implement setMatrixBlood1
}

void Shader::setMatrixBlood2(float[] floats0, float[] floats1) {
  // TODO: Implement setMatrixBlood2
}

void Shader::setShaderAlpha(float a) {
  // TODO: Implement setShaderAlpha
}

void Shader::setLight(int index, float x, float y, float z, float r, float g,
                      float b, float rad, float animPlayerAngle,
                      ModelInstance inst) {
  // TODO: Implement setLight
}

void Shader::doVector3(int int0, float float0, float float1, float float2) {
  // TODO: Implement doVector3
}

void Shader::setHueShift(float hue) {
  // TODO: Implement setHueShift
}

void Shader::setLightingAmount(float lighting) {
  // TODO: Implement setLightingAmount
}

void Shader::setDepthBias(float bias) {
  // TODO: Implement setDepthBias
}

void Shader::setAmbient(float amb) {
  // TODO: Implement setAmbient
}

void Shader::setAmbient(float ambr, float ambg, float ambb) {
  // TODO: Implement setAmbient
}

void Shader::setTransformMatrix(Matrix4f matrix4f, bool transpose) {
  // TODO: Implement setTransformMatrix
}

void Shader::setTransformMatrix(org.joml.Matrix4f matrix4f, bool transpose) {
  // TODO: Implement setTransformMatrix
}

void Shader::setMatrix(int location, org.joml.Matrix4f matrix4f) {
  // TODO: Implement setMatrix
}

void Shader::setMatrix(int int0, float[] floats) {
  // TODO: Implement setMatrix
}

bool Shader::isVehicleShader() {
  // TODO: Implement isVehicleShader
  return false;
}

} // namespace shader
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
