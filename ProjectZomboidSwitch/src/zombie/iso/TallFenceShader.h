#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <GL/glew.h>
#include "zombie/IndieGL.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/core/opengl/ShaderProgram.h"

namespace zombie {
namespace iso {


class TallFenceShader {
public:
    static const TallFenceShader instance = std::make_shared<TallFenceShader>();
    ShaderProgram shaderProgram;
    int u_alpha;
    int u_outlineColor;
    int u_stepSize;

    void initShader() {
      this.shaderProgram = ShaderProgram.createShaderProgram("tallFence", false, true);
      if (this.shaderProgram.isCompiled()) {
         this.u_alpha = ARBShaderObjects.glGetUniformLocationARB(this.shaderProgram.getShaderID(), "u_alpha");
         this.u_stepSize = ARBShaderObjects.glGetUniformLocationARB(this.shaderProgram.getShaderID(), "u_stepSize");
         this.u_outlineColor = ARBShaderObjects.glGetUniformLocationARB(this.shaderProgram.getShaderID(), "u_outlineColor");
         ARBShaderObjects.glUseProgramObjectARB(this.shaderProgram.getShaderID());
         ARBShaderObjects.glUniform2fARB(this.u_stepSize, 0.001F, 0.001F);
         ARBShaderObjects.glUseProgramObjectARB(0);
      }
   }

    void setAlpha(float var1) {
      SpriteRenderer.instance.ShaderUpdate1f(this.shaderProgram.getShaderID(), this.u_alpha, var1);
   }

    void setOutlineColor(float var1, float var2, float var3, float var4) {
      SpriteRenderer.instance.ShaderUpdate4f(this.shaderProgram.getShaderID(), this.u_outlineColor, var1, var2, var3, var4);
   }

    void setStepSize(float var1, int var2, int var3) {
      SpriteRenderer.instance.ShaderUpdate2f(this.shaderProgram.getShaderID(), this.u_stepSize, var1 / var2, var1 / var3);
   }

    bool StartShader() {
      if (this.shaderProgram == nullptr) {
         RenderThread.invokeOnRenderContext(this::initShader);
      }

      if (this.shaderProgram.isCompiled()) {
         IndieGL.StartShader(this.shaderProgram.getShaderID(), 0);
    return true;
      } else {
    return false;
      }
   }
}
} // namespace iso
} // namespace zombie
