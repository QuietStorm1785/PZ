#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <GL/glew.h>
#include "zombie/core/textures/Texture.h"
#include "zombie/core/textures/TextureDraw.h"

namespace zombie {
namespace core {
namespace opengl {


class Shader {
public:
   public static std::unordered_map<int, Shader> ShaderMap = std::make_unique<std::unordered_map<>>();
    std::string name;
    int m_shaderMapID = 0;
    const ShaderProgram m_shaderProgram;
    Texture tex;
    int width;
    int height;

    public Shader(const std::string& var1) {
      this.name = var1;
      this.m_shaderProgram = ShaderProgram.createShaderProgram(var1, false, false);
      this.m_shaderProgram.addCompileListener(this);
      this.m_shaderProgram.compile();
   }

    void setTexture(Texture var1) {
      this.tex = var1;
   }

    int getID() {
      return this.m_shaderProgram.getShaderID();
   }

    void Start() {
      ARBShaderObjects.glUseProgramObjectARB(this.m_shaderProgram.getShaderID());
   }

    void End() {
      ARBShaderObjects.glUseProgramObjectARB(0);
   }

    void destroy() {
      this.m_shaderProgram.destroy();
      ShaderMap.remove(this.m_shaderMapID);
      this.m_shaderMapID = 0;
   }

    void startMainThread(TextureDraw var1, int var2) {
   }

    void startRenderThread(TextureDraw var1) {
   }

    void postRender(TextureDraw var1) {
   }

    bool isCompiled() {
      return this.m_shaderProgram.isCompiled();
   }

    void callback(ShaderProgram var1) {
      ShaderMap.remove(this.m_shaderMapID);
      this.m_shaderMapID = var1.getShaderID();
      ShaderMap.put(this.m_shaderMapID, this);
      this.onCompileSuccess(var1);
   }

    void onCompileSuccess(ShaderProgram var1) {
   }

    ShaderProgram getProgram() {
      return this.m_shaderProgram;
   }
}
} // namespace opengl
} // namespace core
} // namespace zombie
