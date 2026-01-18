#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/util/vector/Matrix4f.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/iso/Vector2.h"
#include "zombie/iso/Vector3.h"

namespace zombie {
namespace core {
namespace opengl {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class SmartShader {
public:
 const ShaderProgram m_shaderProgram;

 public SmartShader(const std::string& string) {
 this->m_shaderProgram = ShaderProgram.createShaderProgram(string, false, true);
 }

 public SmartShader(const std::string& string, bool boolean0) {
 this->m_shaderProgram = ShaderProgram.createShaderProgram(string, boolean0, true);
 }

 void Start() {
 this->m_shaderProgram.Start();
 }

 void End() {
 this->m_shaderProgram.End();
 }

 void setValue(const std::string& string, float float0) {
 this->m_shaderProgram.setValue(string, float0);
 }

 void setValue(const std::string& string, int int0) {
 this->m_shaderProgram.setValue(string, int0);
 }

 void setValue(const std::string& string, Vector3 vector) {
 this->m_shaderProgram.setValue(string, vector);
 }

 void setValue(const std::string& string, Vector2 vector) {
 this->m_shaderProgram.setValue(string, vector);
 }

 void setVector2f(const std::string& string, float float0, float float1) {
 this->m_shaderProgram.setVector2(string, float0, float1);
 }

 void setVector3f(const std::string& string, float float0, float float1, float float2) {
 this->m_shaderProgram.setVector3(string, float0, float1, float2);
 }

 void setVector4f(const std::string& string, float float0, float float1, float float2, float float3) {
 this->m_shaderProgram.setVector4(string, float0, float1, float2, float3);
 }

 void setValue(const std::string& string, Matrix4f matrix4f) {
 this->m_shaderProgram.setValue(string, matrix4f);
 }

 void setValue(const std::string& string, Texture texture, int int0) {
 this->m_shaderProgram.setValue(string, texture, int0);
 }
}
} // namespace opengl
} // namespace core
} // namespace zombie
