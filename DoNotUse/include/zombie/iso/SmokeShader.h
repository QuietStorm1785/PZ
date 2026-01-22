#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/opengl/ARBShaderObjects.h"
#include "org/lwjgl/opengl/GL11.h"
#include "org/lwjgl/opengl/GL13.h"
#include "zombie/core/opengl/Shader.h"
#include "zombie/core/opengl/ShaderProgram.h"
#include "zombie/core/textures/TextureDraw.h"

namespace zombie {
namespace iso {


class SmokeShader : public Shader {
public:
    int mvpMatrix;
    int FireTime;
    int FireParam;
    int FireTexture;

    public SmokeShader(const std::string& var1) {
      super(var1);
   }

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

    void updateSmokeParams(TextureDraw var1, int var2, float var3) {
    ParticlesFire var4 = ParticlesFire.getInstance();
      GL13.glActiveTexture(33984);
      var4.getFireSmokeTexture().bind();
      GL11.glTexEnvi(8960, 8704, 7681);
      ARBShaderObjects.glUniformMatrix4fvARB(this.mvpMatrix, true, var4.getMVPMatrix());
      ARBShaderObjects.glUniform1fARB(this.FireTime, var3);
      ARBShaderObjects.glUniformMatrix3fvARB(this.FireParam, true, var4.getParametersFire());
      if (this.FireTexture != -1) {
         ARBShaderObjects.glUniform1iARB(this.FireTexture, 0);
      }
   }
}
} // namespace iso
} // namespace zombie
