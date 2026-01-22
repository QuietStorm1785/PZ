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


class SmartShader {
public:
    const ShaderProgram m_shaderProgram;

    public SmartShader(const std::string& var1) {
      this.m_shaderProgram = ShaderProgram.createShaderProgram(var1, false, true);
   }

    public SmartShader(const std::string& var1, bool var2) {
      this.m_shaderProgram = ShaderProgram.createShaderProgram(var1, var2, true);
   }

    void Start() {
      this.m_shaderProgram.Start();
   }

    void End() {
      this.m_shaderProgram.End();
   }

    void setValue(const std::string& var1, float var2) {
      this.m_shaderProgram.setValue(var1, var2);
   }

    void setValue(const std::string& var1, int var2) {
      this.m_shaderProgram.setValue(var1, var2);
   }

    void setValue(const std::string& var1, Vector3 var2) {
      this.m_shaderProgram.setValue(var1, var2);
   }

    void setValue(const std::string& var1, Vector2 var2) {
      this.m_shaderProgram.setValue(var1, var2);
   }

    void setVector2f(const std::string& var1, float var2, float var3) {
      this.m_shaderProgram.setVector2(var1, var2, var3);
   }

    void setVector3f(const std::string& var1, float var2, float var3, float var4) {
      this.m_shaderProgram.setVector3(var1, var2, var3, var4);
   }

    void setVector4f(const std::string& var1, float var2, float var3, float var4, float var5) {
      this.m_shaderProgram.setVector4(var1, var2, var3, var4, var5);
   }

    void setValue(const std::string& var1, Matrix4f var2) {
      this.m_shaderProgram.setValue(var1, var2);
   }

    void setValue(const std::string& var1, Texture var2, int var3) {
      this.m_shaderProgram.setValue(var1, var2, var3);
   }
}
} // namespace opengl
} // namespace core
} // namespace zombie
