#pragma once
#include "org/lwjgl/opengl/ARBShaderObjects.h"
#include "org/lwjgl/opengl/GL11.h"
#include "org/lwjgl/opengl/GL13.h"
#include "zombie/core/opengl/Shader.h"
#include "zombie/core/opengl/ShaderProgram.h"
#include "zombie/core/textures/TextureDraw.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace iso {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class SmokeShader : public Shader {
public:
  int mvpMatrix;
  int FireTime;
  int FireParam;
  int FireTexture;

public
  SmokeShader(const std::string &string) { super(string); }

  void onCompileSuccess(ShaderProgram shaderProgram) {
    int int0 = shaderProgram.getShaderID();
    this.FireTexture =
        ARBShaderObjects.glGetUniformLocationARB(int0, "FireTexture");
    this.mvpMatrix =
        ARBShaderObjects.glGetUniformLocationARB(int0, "mvpMatrix");
    this.FireTime = ARBShaderObjects.glGetUniformLocationARB(int0, "FireTime");
    this.FireParam =
        ARBShaderObjects.glGetUniformLocationARB(int0, "FireParam");
    this.Start();
    if (this.FireTexture != -1) {
      ARBShaderObjects.glUniform1iARB(this.FireTexture, 0);
    }

    this.End();
  }

  void updateSmokeParams(TextureDraw var1, int var2, float float0) {
    ParticlesFire particlesFire = ParticlesFire.getInstance();
    GL13.glActiveTexture(33984);
    particlesFire.getFireSmokeTexture().bind();
    GL11.glTexEnvi(8960, 8704, 7681);
    ARBShaderObjects.glUniformMatrix4fvARB(this.mvpMatrix, true,
                                           particlesFire.getMVPMatrix());
    ARBShaderObjects.glUniform1fARB(this.FireTime, float0);
    ARBShaderObjects.glUniformMatrix3fvARB(this.FireParam, true,
                                           particlesFire.getParametersFire());
    if (this.FireTexture != -1) {
      ARBShaderObjects.glUniform1iARB(this.FireTexture, 0);
    }
  }
}
} // namespace iso
} // namespace zombie
