#include "zombie/core/opengl/Shader.h"

namespace zombie {
namespace core {
namespace opengl {

public
Shader::Shader(const std::string &_name) {
  // TODO: Implement Shader
  return nullptr;
}

void Shader::setTexture(Texture _tex) {
  // TODO: Implement setTexture
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

void Shader::destroy() {
  // TODO: Implement destroy
}

void Shader::startMainThread(TextureDraw texd, int playerIndex) {
  // TODO: Implement startMainThread
}

void Shader::startRenderThread(TextureDraw _tex) {
  // TODO: Implement startRenderThread
}

void Shader::postRender(TextureDraw texd) {
  // TODO: Implement postRender
}

bool Shader::isCompiled() {
  // TODO: Implement isCompiled
  return false;
}

void Shader::callback(ShaderProgram sender) {
  // TODO: Implement callback
}

void Shader::onCompileSuccess(ShaderProgram var1) {
  // TODO: Implement onCompileSuccess
}

ShaderProgram Shader::getProgram() {
  // TODO: Implement getProgram
  return nullptr;
}

} // namespace opengl
} // namespace core
} // namespace zombie
