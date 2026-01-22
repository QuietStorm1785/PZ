#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/opengl/ARBShaderObjects.h"
#include "zombie/IndieGL.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/core/opengl/ShaderProgram.h"

namespace zombie {
namespace iso {


class IsoObject {
public:
   public static const IsoObject$OutlineShader instance = new IsoObject$OutlineShader();
    ShaderProgram shaderProgram;
    int stepSize;
    int outlineColor;

    void initShader() {
      this.shaderProgram = ShaderProgram.createShaderProgram("outline", false, true);
      if (this.shaderProgram.isCompiled()) {
         this.stepSize = ARBShaderObjects.glGetUniformLocationARB(this.shaderProgram.getShaderID(), "stepSize");
         this.outlineColor = ARBShaderObjects.glGetUniformLocationARB(this.shaderProgram.getShaderID(), "outlineColor");
         ARBShaderObjects.glUseProgramObjectARB(this.shaderProgram.getShaderID());
         ARBShaderObjects.glUniform2fARB(this.stepSize, 0.001F, 0.001F);
         ARBShaderObjects.glUseProgramObjectARB(0);
      }
   }

    void setOutlineColor(float var1, float var2, float var3, float var4) {
      SpriteRenderer.instance.ShaderUpdate4f(this.shaderProgram.getShaderID(), this.outlineColor, var1, var2, var3, var4);
   }

    void setStepSize(float var1, int var2, int var3) {
      SpriteRenderer.instance.ShaderUpdate2f(this.shaderProgram.getShaderID(), this.stepSize, var1 / var2, var1 / var3);
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
