
#include "zombie/iso/FireShader.h"
#include "zombie/core/opengl/GLState.h"
#include "zombie/core/opengl/GLShaderUtil.h"
#include "zombie/iso/ParticlesFire.h"

namespace zombie {
namespace iso {

FireShader::FireShader(const std::string& name) : Shader(name) {}

void FireShader::onCompileSuccess(ShaderProgram& program) {
    int shaderId = program.getShaderID();
    FireTexture = GLShaderUtil::getUniformLocation(shaderId, "FireTexture");
    mvpMatrix = GLShaderUtil::getUniformLocation(shaderId, "mvpMatrix");
    FireTime = GLShaderUtil::getUniformLocation(shaderId, "FireTime");
    FireParam = GLShaderUtil::getUniformLocation(shaderId, "FireParam");
    this->Start();
    if (FireTexture != -1) {
        GLShaderUtil::setUniform1i(FireTexture, 0);
    }
    this->End();
}

void FireShader::updateFireParams(TextureDraw& /*draw*/, int /*param*/, float time) {
    ParticlesFire& pf = ParticlesFire::getInstance();
    GLState::activeTexture(0);
    pf.getFireFlameTexture().bind();
    GLState::texEnvi(GLState::TEXTURE_ENV, GLState::TEXTURE_ENV_MODE, GLState::COMBINE);
    GLShaderUtil::setUniformMatrix4fv(mvpMatrix, pf.getMVPMatrix());
    GLShaderUtil::setUniform1f(FireTime, time);
    GLShaderUtil::setUniformMatrix3fv(FireParam, pf.getParametersFire());
    if (FireTexture != -1) {
        GLShaderUtil::setUniform1i(FireTexture, 0);
    }
}

} // namespace iso
} // namespace zombie
