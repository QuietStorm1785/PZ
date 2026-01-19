#pragma once
#include "org/lwjgl/opengl/ARBShaderObjects.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/core/textures/TextureDraw.h"
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace opengl {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Shader {
public:
public
 static HashMap<Integer, Shader> ShaderMap = std::make_unique<HashMap<>>();
 std::string name;
 int m_shaderMapID = 0;
 const ShaderProgram m_shaderProgram;
 Texture tex;
 int width;
 int height;

public
 Shader(std::string_view _name) {
 this->name = _name;
 this->m_shaderProgram =
 ShaderProgram.createShaderProgram(_name, false, false);
 this->m_shaderProgram.addCompileListener(this);
 this->m_shaderProgram.compile();
 }

 void setTexture(Texture _tex) { this->tex = _tex; }

 int getID() { return this->m_shaderProgram.getShaderID(); }

 void Start() {
 ARBShaderObjects.glUseProgramObjectARB(this->m_shaderProgram.getShaderID());
 }

 void End() { ARBShaderObjects.glUseProgramObjectARB(0); }

 void destroy() {
 this->m_shaderProgram.destroy();
 ShaderMap.remove(this->m_shaderMapID);
 this->m_shaderMapID = 0;
 }

 void startMainThread(TextureDraw texd, int playerIndex) {}

 void startRenderThread(TextureDraw _tex) {}

 void postRender(TextureDraw texd) {}

 bool isCompiled() { return this->m_shaderProgram.isCompiled(); }

 void callback(ShaderProgram sender) {
 ShaderMap.remove(this->m_shaderMapID);
 this->m_shaderMapID = sender.getShaderID();
 ShaderMap.put(this->m_shaderMapID, this);
 this->onCompileSuccess(sender);
 }

 void onCompileSuccess(ShaderProgram var1) {}

 ShaderProgram getProgram() { return this->m_shaderProgram; }
}
} // namespace opengl
} // namespace core
} // namespace zombie
