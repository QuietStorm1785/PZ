#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#ifdef NINTENDO_SWITCH
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_opengles2.h>
#else
#include "zombie/core/opengl/GLState.h"
#include "zombie/core/opengl/GLShaderUtil.h"
#endif
#include "zombie/core/opengl/Shader.h"
#include "zombie/core/opengl/ShaderProgram.h"
#include "zombie/core/textures/TextureDraw.h"

namespace zombie {
namespace iso {


class FireShader : public Shader {
public:
    int mvpMatrix;
    int FireTime;
    int FireParam;
    int FireTexture;

    FireShader(const std::string& name) : Shader(name) {}

    void onCompileSuccess(ShaderProgram var1) {
    int var2 = var1.getShaderID();
      this.FireTexture = ARBShaderObjects.glGetUniformLocationARB(var2, "FireTexture");
      this.mvpMatrix = ARBShaderObjects.glGetUniformLocationARB(var2, "mvpMatrix");
      this.FireTime = ARBShaderObjects.glGetUniformLocationARB(var2, "FireTime");
      this.FireParam = ARBShaderObjects.glGetUniformLocationARB(var2, "FireParam");
      this.Start();
      if (this.FireTexture != -1) {
         ARBShaderObjects.glUniform1iARB(this.FireTexture, 0);
      }

      this.End();
   }

    void updateFireParams(TextureDraw var1, int var2, float var3) {
    ParticlesFire var4 = ParticlesFire.getInstance();
      GL13.glActiveTexture(33984);
      var4.getFireFlameTexture().bind();
      GL11.glTexEnvi(8960, 8704, 7681);
      ARBShaderObjects.glUniformMatrix4fvARB(this.mvpMatrix, true, var4.getMVPMatrix());
      ARBShaderObjects.glUniform1fARB(this.FireTime, var3);
      ARBShaderObjects.glUniformMatrix3fvARB(this.FireParam, true, var4.getParametersFire());
      if (this.FireTexture != -1) {
         ARBShaderObjects.glUniform1iARB(this.FireTexture, 0);
      }
   }
    void onCompileSuccess(ShaderProgram& program) override;
    void updateFireParams(TextureDraw& draw, int param, float time);
};
}
} // namespace iso
} // namespace zombie
